/* === S Y N F I G ========================================================= */
/*!	\file value_desc.cpp
**	\brief Template File
**
**	$Id$
**
**	\legal
**	Copyright (c) 2008 Chris Moore
**	Copyright (c) 2009 Nikita Kitaev
**
**	This package is free software; you can redistribute it and/or
**	modify it under the terms of the GNU General Public License as
**	published by the Free Software Foundation; either version 2 of
**	the License, or (at your option) any later version.
**
**	This package is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
**	General Public License for more details.
**	\endlegal
*/
/* ========================================================================= */

/* === H E A D E R S ======================================================= */

#ifdef USING_PCH
#	include "pch.h"
#else
#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include "value_desc.h"
#include <string>

#include "general.h"

#endif

/* === U S I N G =========================================================== */

using namespace std;
using namespace etl;
using namespace synfig;
using namespace synfigapp;

/* === M A C R O S ========================================================= */

/* === M E T H O D S ======================================================= */

String
ValueDesc::get_description(bool show_exported_name)const
{
	String description;

	if (show_exported_name && !is_exported())
		show_exported_name = false;

	if (parent_is_layer_param())
	{
		description = strprintf("%s (%s):%s", _("Layer Parameter"),
								get_layer()->get_non_empty_description().c_str(),
								get_layer()->get_param_local_name(get_param_name()).c_str());
		if (show_exported_name)
			description += strprintf(" (%s)", get_value_node()->get_id().c_str());
	}
	else if (parent_is_value_node())
	{
		if (parent_is_linkable_value_node())
		{
			synfig::LinkableValueNode::Handle value_node(synfig::LinkableValueNode::Handle::cast_reinterpret(get_parent_value_node()));
			description = strprintf("%s %s", _("ValueNode"),
									value_node->get_description(get_index(), show_exported_name).c_str());
		}
		else if (parent_is_value_node_const())
		{
			synfig::ValueNode_Const::Handle value_node(synfig::ValueNode_Const::Handle::cast_reinterpret(get_parent_value_node()));
			description = strprintf("%s %s", _("Const ValueNode"),
									value_node->get_description(show_exported_name).c_str());
		}
		else if (parent_is_waypoint())
			description = _("Waypoint");
		else
		{
			warning("%s:%d didn't expect to get here", __FILE__, __LINE__);
			assert(0);
		}
	}
	else if (parent_is_canvas())
		description = strprintf("%s (%s)", _("Exported ValueNode"),
								get_value_node()->get_id().c_str());
	else
		description = "Unknown ValueDesc type";

	return description;
}

ValueDesc::ValueDesc(synfig::Layer::Handle layer,const synfig::String& param_name):
	layer(layer),
	name(param_name)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

ValueDesc::ValueDesc(synfig::Layer::LooseHandle layer,const synfig::String& param_name):
	layer(layer),
	name(param_name)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

ValueDesc::ValueDesc(synfig::LinkableValueNode::Handle parent_value_node,int index):
	parent_value_node(parent_value_node),
	index(index)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

// ValueDesc::ValueDesc(synfig::LinkableValueNode::Handle parent_value_node,const synfig::String& param_name):
// 	parent_value_node(parent_value_node),
// 	index(parent_value_node->get_link_index_from_name(param_name)) { }

ValueDesc::ValueDesc(synfig::ValueNode_Animated::Handle parent_value_node,synfig::Time waypoint_time):
	parent_value_node(parent_value_node),
	index(-2),
	waypoint_time(waypoint_time)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

ValueDesc::ValueDesc(synfig::Canvas::Handle canvas,const synfig::String& name):
	name(name),
	canvas(canvas)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

ValueDesc::ValueDesc(synfig::ValueNode_Const::Handle parent_value_node):
	parent_value_node(parent_value_node),
	index(-1)
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (%s)\n", __FILE__, __LINE__, ulong(this), get_description().c_str());
}

ValueDesc::ValueDesc()
{
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d construct ValueDesc %lx (blank)\n", __FILE__, __LINE__, ulong(this));
}

// copy constructor
ValueDesc::ValueDesc(const ValueDesc &old)
{
	layer = old.layer;
	name = old.name;
	parent_value_node = old.parent_value_node;
	index = old.index;
	waypoint_time = old.waypoint_time;
	canvas = old.canvas;
	if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
		printf("%s:%d copy constructor for %lx <-- %lx (...)\n", __FILE__, __LINE__, ulong(this), ulong(&old));
}

// assignment operator
ValueDesc&
ValueDesc::operator=(const ValueDesc& that)
{
	if (this != &that)
	{
		layer = that.layer;
		name = that.name;
		parent_value_node = that.parent_value_node;
		index = that.index;
		waypoint_time = that.waypoint_time;
		canvas = that.canvas;
		if (getenv("SYNFIG_DEBUG_VALUE_DESC_CONSTRUCTORS"))
			printf("%s:%d assignment operator for %lx <-- %lx (...)\n", __FILE__, __LINE__, ulong(this), ulong(&that));
	}

    return *this;
}

/* === S Y N F I G ========================================================= */
/*!	\file valuenode_vectorx.cpp
**	\brief Implementation of the "Vector X" valuenode conversion.
**
**	$Id$
**
**	\legal
**	Copyright (c) 2002-2005 Robert B. Quattlebaum Jr., Adrian Bentley
**	Copyright (c) 2007, 2008 Chris Moore
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

#include "valuenode_vectorx.h"
#include "valuenode_const.h"
#include "general.h"

#endif

/* === U S I N G =========================================================== */

using namespace std;
using namespace etl;
using namespace synfig;

/* === M A C R O S ========================================================= */

/* === G L O B A L S ======================================================= */

/* === P R O C E D U R E S ================================================= */

/* === M E T H O D S ======================================================= */

ValueNode_VectorX::ValueNode_VectorX(const ValueBase &value):
	LinkableValueNode(value.get_type())
{
	switch(value.get_type())
	{
	case ValueBase::TYPE_REAL:
		set_link("vector",ValueNode_Const::create(Vector(value.get(Real()), 0)));
		break;
	default:
		throw Exception::BadType(ValueBase::type_local_name(value.get_type()));
	}

	DCAST_HACK_ENABLE();
}

LinkableValueNode*
ValueNode_VectorX::create_new()const
{
	return new ValueNode_VectorX(get_type());
}

ValueNode_VectorX*
ValueNode_VectorX::create(const ValueBase &x)
{
	return new ValueNode_VectorX(x);
}

ValueNode_VectorX::~ValueNode_VectorX()
{
	unlink_all();
}

ValueBase
ValueNode_VectorX::operator()(Time t)const
{
	if (getenv("SYNFIG_DEBUG_VALUENODE_OPERATORS"))
		printf("%s:%d operator()\n", __FILE__, __LINE__);

	return (*vector_)(t).get(Vector())[0];
}


bool
ValueNode_VectorX::set_link_vfunc(int i,ValueNode::Handle value)
{
	assert(i>=0 && i<link_count());

	switch(i)
	{
	case 0: CHECK_TYPE_AND_SET_VALUE(vector_, ValueBase::TYPE_VECTOR);
	}
	return false;
}

ValueNode::LooseHandle
ValueNode_VectorX::get_link_vfunc(int i)const
{
	assert(i>=0 && i<link_count());

	if(i==0)
		return vector_;
	return 0;
}

int
ValueNode_VectorX::link_count()const
{
	return 1;
}

String
ValueNode_VectorX::link_local_name(int i)const
{
	assert(i>=0 && i<link_count());

	if(i==0)
		return _("Vector");
	return String();
}

String
ValueNode_VectorX::link_name(int i)const
{
	assert(i>=0 && i<link_count());

	if(i==0)
		return "vector";
	return String();
}

int
ValueNode_VectorX::get_link_index_from_name(const String &name)const
{
	if(name=="vector")
		return 0;

	throw Exception::BadLinkName(name);
}

String
ValueNode_VectorX::get_name()const
{
	return "vectorx";
}

String
ValueNode_VectorX::get_local_name()const
{
	return _("Vector X");
}

bool
ValueNode_VectorX::check_type(ValueBase::Type type)
{
	return type==ValueBase::TYPE_REAL;
}
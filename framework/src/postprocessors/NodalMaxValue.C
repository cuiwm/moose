/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "NodalMaxValue.h"

#include <algorithm>
#include <limits>

template <>
InputParameters
validParams<NodalMaxValue>()
{
  InputParameters params = validParams<NodalVariablePostprocessor>();
  return params;
}

NodalMaxValue::NodalMaxValue(const InputParameters & parameters)
  : NodalVariablePostprocessor(parameters), _value(-std::numeric_limits<Real>::max())
{
}

void
NodalMaxValue::initialize()
{
  _value = -std::numeric_limits<Real>::max();
}

void
NodalMaxValue::execute()
{
  _value = std::max(_value, _u[_qp]);
}

Real
NodalMaxValue::getValue()
{
  gatherMax(_value);
  return _value;
}

void
NodalMaxValue::threadJoin(const UserObject & y)
{
  const NodalMaxValue & pps = static_cast<const NodalMaxValue &>(y);
  _value = std::max(_value, pps._value);
}

/*
* MIT License
*
* Copyright (c) 2017 Dmitry Smirnov
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "ComplexStateMachine.h"

//-------- StateBuilder --------//

StateBuilder::StateBuilder(ComplexStateMachine& stateMachine,
                           const State& state) :
    _stateMachine(stateMachine),
    _state(state)
{}

StateBuilder&
StateBuilder::setStateFunction(StateFunction function)
{
    _stateMachine.setStateFunction(_state, function);
    return *this;
}

StateBuilder&
StateBuilder::setStateRequirements(const StateList& requirements)
{
    _stateMachine.setStateRequirements(_state, requirements);
    return *this;
}

StateBuilder&
StateBuilder::setStateIncompatibilities(const StateList& incompatibilities)
{
    _stateMachine.setStateIncompatibilities(_state, incompatibilities);
    return *this;
}

//-------- ComplexStateMachine --------//

const ComplexStateMachine::ComplexState&
ComplexStateMachine::complexState() const
{
    return _complexState;
}

void
ComplexStateMachine::activateState(const State& state)
{
    for (const State& s : stateIncompatibilities(state))
        deactivateState(s);

    if (isStateActive(state))
        return;

    _complexState.push_back(state);
}

void
ComplexStateMachine::deactivateState(const State& state)
{
    if (!isStateActive(state))
        return;

    _complexState.erase(std::find(_complexState.begin(), _complexState.end(),
                                  state));
}

bool
ComplexStateMachine::isStateActive(const State& state)
{
    return std::find(_complexState.begin(), _complexState.end(), state) !=
            _complexState.end();
}

const StateFunction&
ComplexStateMachine::stateFunction(const State& state)
{
    try
    {
        return _stateFunctions.at(state);
    }
    catch (std::out_of_range&)
    {
        return DO_NOTHING;
    }
}

void
ComplexStateMachine::setStateFunction(const State& state, StateFunction function)
{
    _stateFunctions[state] = function;
}

void
ComplexStateMachine::callStateFunction(const State& state)
{
    const StateFunction& function = stateFunction(state);
    function();
}

void
ComplexStateMachine::callComplexStateFunctions()
{
    for (const State& state : complexState())
        callStateFunction(state);
}

const StateList&
ComplexStateMachine::stateRequirements(const State& state)
{
    try
    {
        return _stateRequirements.at(state);
    }
    catch (std::out_of_range&)
    {
        return EMPTY_COMPLEX_STATE;
    }
}

void
ComplexStateMachine::setStateRequirements(const State& state,
                                          const StateList& requirements)
{
    _stateRequirements[state] = requirements;
}

const StateList&
ComplexStateMachine::stateIncompatibilities(const State& state)
{
    try
    {
        return _stateIncompatibilities.at(state);
    }
    catch (std::out_of_range&)
    {
        return EMPTY_COMPLEX_STATE;
    }
}

void
ComplexStateMachine::setStateIncompatibilities(const State& state,
                                            const StateList& incompatibilities)
{
    _stateIncompatibilities[state] = incompatibilities;
}

StateBuilder
ComplexStateMachine::stateBuilder(const State& state)
{
    return StateBuilder(*this, state);
}

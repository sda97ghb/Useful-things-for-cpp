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

#ifndef COMPLEX_STATE_MACHINE_H
#define COMPLEX_STATE_MACHINE_H

#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <string>

using State = const std::string;
#define STATE(stateName) \
    State stateName##State{#stateName};

using StateList = std::list<std::remove_const<State>::type>;
static const StateList EMPTY_COMPLEX_STATE{};

using StateFunction = std::function<void()>;
static const StateFunction DO_NOTHING{[](){}};
#define METHOD_FUNCTION(methodName) \
    [&](){methodName();}

class ComplexStateMachine;

class StateBuilder
{
public:
    StateBuilder(ComplexStateMachine& stateMachine, const State& state);

    StateBuilder& setStateFunction(StateFunction function);
    StateBuilder& setStateRequirements(const StateList& requirements);
    StateBuilder& setStateIncompatibilities(const StateList& incompatibilities);

private:
    ComplexStateMachine& _stateMachine;
    const State _state;
};

class ComplexStateMachine
{
public:
    using ComplexState = StateList;

    const ComplexState& complexState() const;

    void activateState(const State& state);
    void deactivateState(const State& state);

    bool isStateActive(const State& state);

    const StateFunction& stateFunction(const State& state);
    void setStateFunction(const State& state, StateFunction function);
    void callStateFunction(const State& state);
    void callComplexStateFunctions();

    const StateList& stateRequirements(const State& state);
    void setStateRequirements(const State& state, const StateList& requirements);

    const StateList& stateIncompatibilities(const State& state);
    void setStateIncompatibilities(const State& state, const StateList& incompatibilities);

    StateBuilder stateBuilder(const State& state);

private:
    ComplexState _complexState;
    std::map<State, StateFunction> _stateFunctions;
    std::map<State, std::list<std::remove_const<State>::type>> _stateRequirements;
    std::map<State, std::list<std::remove_const<State>::type>> _stateIncompatibilities;
};

#endif // COMPLEX_STATE_MACHINE_H

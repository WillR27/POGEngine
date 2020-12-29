#include "pgepch.h"
#include "InputPackage.h"

namespace PEngine
{
    bool InputPackage::HasActionOccurred(std::string name, bool remove)
    {
        auto it = actions.begin();

        for (; it != actions.end();)
        {
            Action& action = *it;

            if (action.name == name)
            {
                if (remove)
                {
                    actions.erase(it);
                }

                return true;
            }
            else
            {
                it++;
            }
        }

        return false;
    }

    void InputPackage::AddAction(Action action)
    {
        actions.push_back(action);
    }

    bool InputPackage::IsStateActive(std::string name, bool remove)
    {
        auto it = states.begin();

        for (; it != states.end();)
        {
            State& state = *it;

            if (state.name == name)
            {
                if (remove)
                {
                    states.erase(it);
                }

                return state.IsOn();
            }
            else
            {
                it++;
            }
        }

        return false;
    }

    void InputPackage::AddState(State state)
    {
        states.push_back(state);
    }

    int InputPackage::GetAxisValue(std::string name, bool remove)
    {
        auto it = axes.begin();

        for (; it != axes.end();)
        {
            Axis& axis= *it;

            if (axis.name == name)
            {
                if (remove)
                {
                    axes.erase(it);
                }

                return axis.GetValue();
            }
            else
            {
                it++;
            }
        }

        return 0;
    }

    void InputPackage::AddAxis(Axis axis)
    {
        axes.push_back(axis);
    }

    void InputPackage::Clear()
    {
        actions.clear();
        states.clear();
        axes.clear();
    }

    bool InputPackage::IsEmpty() const
    {
        return actions.size() == 0 && states.size() == 0 && axes.size() == 0;
    }
}
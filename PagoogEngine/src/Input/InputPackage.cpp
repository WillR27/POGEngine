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
        for (Action& existingAction : actions)
        {
            if (existingAction.name == action.name)
            {
                PG_WARN("Did not add action to the input package! Action \"{0}\" already exists in the input package.", existingAction.name);
            }
        }

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

    void InputPackage::AddOrReplaceState(State state)
    {
        auto it = states.begin();

        for (; it != states.end();)
        {
            State& existingSstate = *it;

            if (existingSstate.name == state.name)
            {
                states.erase(it);

                break;
            }
            else
            {
                it++;
            }
        }

        states.push_back(state);
    }

    void InputPackage::Clear()
    {
        actions.clear();
        states.clear();
    }

    bool InputPackage::IsEmpty() const
    {
        return actions.size() == 0 && states.size() == 0;
    }
}
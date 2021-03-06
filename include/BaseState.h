//
// Created by M on 4/13/21.
//


#ifndef CSCI437_BASESTATE_H
#define CSCI437_BASESTATE_H


#pragma once
#include <SFML/Graphics.hpp>
class ProcessManager;
class BaseState
{
    friend class ProcessManager;

public:
    BaseState(ProcessManager* l_processManager):
            m_stateMgr(l_processManager), m_transparent(false),
            m_transcendent(false){}
    virtual ~BaseState(){}

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update(const sf::Time& l_time) = 0;
    virtual void Draw() = 0;

    void SetTransparent (const bool& l_transparent) {
        m_transparent = l_transparent;
    }

    bool IsTransparent()const
    {
        return m_transparent;
    }
    void SetTranscendent(const bool& l_transcendence)
    {
        m_transcendent = l_transcendence;
    }

    bool IsTranscendent()const
    {
        return m_transcendent;
    }

    ProcessManager* GetProcessManager()
    {
        return m_stateMgr;
    }

protected:
    ProcessManager* m_stateMgr;
    bool m_transparent;
    bool m_transcendent;
    sf::View m_view;
};


#endif //CSCI437_BASESTATE_H

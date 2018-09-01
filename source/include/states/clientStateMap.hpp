#pragma once

#include <gui/states/stateMap.hpp>
#include "states/playing.hpp"
#include "states/loading.hpp"
#include "states/mainMenu.hpp"
#include "states/options.hpp"

class ClientStateMap : public StateMap
{
public:
    ClientStateMap(){}

    ~ClientStateMap() override {}

    void initStateMap() override
    {
        m_stateMap.insert(std::make_pair("mainMenu", std::shared_ptr<GameState>( new MainMenu() ) ) );
        m_stateMap.insert(std::make_pair("playing", std::shared_ptr<GameState>( new Playing() ) ) );
        m_stateMap.insert(std::make_pair("loading", std::shared_ptr<GameState>( new Loading() ) ) );
        m_stateMap.insert(std::make_pair("options", std::shared_ptr<GameState>( new Options() ) ) );
    }
};

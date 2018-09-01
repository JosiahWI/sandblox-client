/*
 *	 Copyright (C) 2018 Qub³d Engine Group.
 *	 All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *  
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without
 *  specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <GL/glew.h>
#include "states/playing.hpp"

void Playing::draw( )
{
    ImGuiHelper::prepareDraw(m_io);
	// Always remember to clear the window
	glClearColor( 0.0f, 0.0f, 0.5f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT );
    ImGuiHelper::draw();
}

void Playing::update( )
{
    ImGuiHelper::updateFrame();

    ImGui::Begin("Playing");

    if(ImGui::Button("Back", ImVec2(100,30)))
    {
        g_Client->getStateManager()->popState();
    }

    ImGui::End();
}

void Playing::handleEvent( SDL_Event& event )
{
    ImGuiHelper::handleEvents(event);
    if ( event.type == SDL_WINDOWEVENT )
    {
        switch ( event.window.event )
        {
        case SDL_WINDOWEVENT_CLOSE:
            // Yes the window should close.
            g_Client->setIsRunning( false );
            break;
        }
    }
    std::shared_ptr<Command> inputCommand = m_inputHandler->handleInput( event );
    // if the command is null, that means nothing happened or something happened that was not handled.
    if ( inputCommand != nullptr )
    {
        inputCommand->execute( event );
    }
}

/*
 * This runs immediately after the GameStateManager changes states.
 */
void Playing::enter( )
{
	m_inputHandler->initCommandMap( );
	// TODO: Read profile settings to determine which keymap to read from.
    m_inputHandler->initInputCommands( "testing.keymap" );

    ImGuiHelper::init(m_io);
}

/*
 * This runs before the GameStateManager changes states.
 */
void Playing::exit( )
{
    ImGuiHelper::quit();
}

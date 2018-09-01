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

#include "client.hpp"
#include "states/clientStateMap.hpp"
#include <cstdlib>
#include <sstream>

Client::Client( )
{

}

Client::~Client( )
{

}

void Client::run( )
{
	initSystems( );
	mainGameLoop( );
	quitGame( );
}

bool Client::isRunning( )
{
	return m_isRunning;
}

void Client::setIsRunning( bool isRunning )
{
	m_isRunning = isRunning;
}

std::shared_ptr<GameStateManager> Client::getStateManager( )
{
	return m_stateManager;
}

SDL_Window* Client::getWindow( )
{
	return m_mainWindow;
}

SDL_GLContext Client::getGLContext( )
{
	return m_glContext;
}

void Client::initSystems( )
{
	// Using namespace qub3d for cleaner code.
	//using namespace qub3d;

	/*
	 * Intialise logger with logging file path and logging verbosity, which is set to everything,
	 * this will be until the Settings manager is implemented
	*/

	char* dataPath;
	char* basePath = SDL_GetBasePath( );
	dataPath = basePath ? basePath : SDL_strdup( ". /" );


	string_t logging_path( dataPath );

	m_logger = std::shared_ptr<qub3d::Logger>( new qub3d::Logger( ) );
	m_logger->init( logging_path + "/client.log", qub3d::LogVerbosity::DEBUG );

	//-----------------SDL and openGL-------------------

	SDL_Init( SDL_INIT_EVERYTHING );

	m_mainWindow = SDL_CreateWindow(
									 "Qub3d",
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 800, 600,
									 SDL_WINDOW_OPENGL );
	if ( m_mainWindow == nullptr )
	{
		// In the case that the window could not be made...
		ERROR( string_t("Could not create window: ") + SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	m_glContext = SDL_GL_CreateContext( m_mainWindow );
	if ( m_glContext == nullptr )
	{
		ERROR( string_t("Could not create OpenGL Context: ") + SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	GLenum err = glewInit( );
	if ( err != GLEW_OK )
	{
		// Problem: glewInit failed, something is seriously wrong.
		std::stringstream message; // Create a use LogMessage_t (typedef for stringstream), not just concentating with "+", because glewGetErrorString is a grumpy function.
		message  << "GLEW initialisation failed: " << glewGetErrorString( err );
		ERROR( message.str() );
		exit( EXIT_FAILURE );
	}

	// Print out GLEW version for confirmation
	std::stringstream message; // Create a use LogMessage_t (typedef for stringstream), not just concentating with "+", because glewGetErrorString is a grumpy function.
	message  << "Status: Using GLEW version " << glewGetString( GLEW_VERSION );
	DEBUG(message.str());

	glewExperimental = true;

	//----------------member variables------------------

    m_stateManager = std::shared_ptr<GameStateManager>( new GameStateManager( std::shared_ptr<StateMap>( new ClientStateMap() ) ) );

    m_stateManager->init( "mainMenu" );

	INFO( "Systems Initialized & Client Started!" );
}

void Client::mainGameLoop( )
{
	m_isRunning = true;

	while ( m_isRunning )
    {
        m_stateManager->step();

        SDL_GL_SwapWindow( m_mainWindow );
	}
}

void Client::quitGame( )
{
	INFO("Quitting the Client");
	SDL_DestroyWindow( m_mainWindow );
	SDL_Quit( );
	// Destroy logger to close the files.
	m_logger->destroy( );
}

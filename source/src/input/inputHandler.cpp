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

#include "input/inputHandler.hpp"
#include <SDL_filesystem.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>



// Wrapper for much cleaner code.
void InputHandler::setCommand( const string_t& name, std::shared_ptr<Command> command )
{
	m_commandMap[name] = command;
}

void InputHandler::insertCommandIntoMap( const string_t& name, std::shared_ptr<Command> command )
{
	m_commandMap.insert( std::make_pair( name, command ) );
}

std::shared_ptr<Command> InputHandler::getCommandByName(const string_t& type)
{
	if(type == "ReturnToMain")
	{
		return std::shared_ptr<Command>(new ReturnToMainCommand());
	}
	DEBUG("Returning nullptr");
	return nullptr;
}

void InputHandler::initInputCommands( const string_t& filename )
{
	char* dataPath;
	char* basePath = SDL_GetBasePath( );
	if ( basePath )
	{
		dataPath = basePath;
	} else
	{
		dataPath = SDL_strdup( "./" );
	}

	std::ifstream keyFile(std::string(dataPath) + filename);

	std::string line;
	while(std::getline(keyFile, line))
	{
		std::istringstream iss(line);
		std::string token;
		std::vector<std::string> tokens;

		/*
		 *  We use the ',' delimiter to split each keymapping.
		 * Example: "A,Forward"
		 */
		while(std::getline(iss, token, ','))
		{
			tokens.push_back(token);
		}

		setCommand(tokens[0],getCommandByName(tokens[1]));
	}

}

void InputHandler::initCommandMap( )
{
	// using a local variable because nullptr itself does not cast to a std::shared_ptr<Command>
	std::shared_ptr<Command> nullptr_command = nullptr;
	insertCommandIntoMap( "A", nullptr_command );
	insertCommandIntoMap( "B", nullptr_command );
	insertCommandIntoMap( "C", nullptr_command );
	insertCommandIntoMap( "D", nullptr_command );
	insertCommandIntoMap( "E", nullptr_command );
	insertCommandIntoMap( "F", nullptr_command );
	insertCommandIntoMap( "G", nullptr_command );
	insertCommandIntoMap( "H", nullptr_command );
	insertCommandIntoMap( "I", nullptr_command );
	insertCommandIntoMap( "J", nullptr_command );
	insertCommandIntoMap( "K", nullptr_command );
	insertCommandIntoMap( "L", nullptr_command );
	insertCommandIntoMap( "M", nullptr_command );
	insertCommandIntoMap( "N", nullptr_command );
	insertCommandIntoMap( "O", nullptr_command );
	insertCommandIntoMap( "P", nullptr_command );
	insertCommandIntoMap( "Q", nullptr_command );
	insertCommandIntoMap( "R", nullptr_command );
	insertCommandIntoMap( "S", nullptr_command );
	insertCommandIntoMap( "T", nullptr_command );
	insertCommandIntoMap( "U", nullptr_command );
	insertCommandIntoMap( "V", nullptr_command );
	insertCommandIntoMap( "W", nullptr_command );
	insertCommandIntoMap( "X", nullptr_command );
	insertCommandIntoMap( "Y", nullptr_command );
	insertCommandIntoMap( "Z", nullptr_command );
	insertCommandIntoMap( "1", nullptr_command );
	insertCommandIntoMap( "2", nullptr_command );
	insertCommandIntoMap( "3", nullptr_command );
	insertCommandIntoMap( "4", nullptr_command );
	insertCommandIntoMap( "5", nullptr_command );
	insertCommandIntoMap( "6", nullptr_command );
	insertCommandIntoMap( "7", nullptr_command );
	insertCommandIntoMap( "8", nullptr_command );
	insertCommandIntoMap( "9", nullptr_command );
	insertCommandIntoMap( "0", nullptr_command );
	insertCommandIntoMap( "F1", nullptr_command );
	insertCommandIntoMap( "F2", nullptr_command );
	insertCommandIntoMap( "F3", nullptr_command );
	insertCommandIntoMap( "F4", nullptr_command );
	insertCommandIntoMap( "F5", nullptr_command );
	insertCommandIntoMap( "F6", nullptr_command );
	insertCommandIntoMap( "F7", nullptr_command );
	insertCommandIntoMap( "F8", nullptr_command );
	insertCommandIntoMap( "F9", nullptr_command );
	insertCommandIntoMap( "F10", nullptr_command );
	insertCommandIntoMap( "F11", nullptr_command );
	insertCommandIntoMap( "F12", nullptr_command );
	insertCommandIntoMap( "LALT", nullptr_command );
	insertCommandIntoMap( "RALT", nullptr_command );
	insertCommandIntoMap( "LCTRL", nullptr_command );
	insertCommandIntoMap( "RCTRL", nullptr_command );
	insertCommandIntoMap( "UP", nullptr_command );
	insertCommandIntoMap( "DOWN", nullptr_command );
	insertCommandIntoMap( "LEFT", nullptr_command );
	insertCommandIntoMap( "RIGHT", nullptr_command );
	insertCommandIntoMap( "TAB", nullptr_command );
	insertCommandIntoMap( "BACKSPACE", nullptr_command );
	insertCommandIntoMap( "CAPSLOCK", nullptr_command );
	insertCommandIntoMap( "BACKSLASH", nullptr_command );
	insertCommandIntoMap( "COMMA", nullptr_command );
	insertCommandIntoMap( "PERIOD", nullptr_command );
	insertCommandIntoMap( "RETURN", nullptr_command );
	insertCommandIntoMap( "QUOTE", nullptr_command );
	insertCommandIntoMap( "SPACEBAR", nullptr_command );
	insertCommandIntoMap( "DELETE", nullptr_command );
	insertCommandIntoMap( "END", nullptr_command );
	insertCommandIntoMap( "HOME", nullptr_command );
	insertCommandIntoMap( "INSERT", nullptr_command );
	insertCommandIntoMap( "BACKQUOTE", nullptr_command );
	insertCommandIntoMap( "MENU", nullptr_command );
	insertCommandIntoMap( "PAGEUP", nullptr_command );
	insertCommandIntoMap( "PAGEDOWN", nullptr_command );
	insertCommandIntoMap( "EQUALS", nullptr_command );
	insertCommandIntoMap( "MINUS", nullptr_command );
	insertCommandIntoMap( "SEMICOLON", nullptr_command );
	insertCommandIntoMap( "RIGHTBRACKET", nullptr_command );
	insertCommandIntoMap( "LEFTBRACKET", nullptr_command );
	insertCommandIntoMap( "SLASH", nullptr_command );
	insertCommandIntoMap( "LEFT_MOUSE", nullptr_command );
	insertCommandIntoMap( "RIGHT_MOUSE", nullptr_command );
	insertCommandIntoMap( "MIDDLE_MOUSE", nullptr_command );
	insertCommandIntoMap( "X1_MOUSE", nullptr_command );
	insertCommandIntoMap( "X2_MOUSE", nullptr_command );
	insertCommandIntoMap( "MOUSEWHEEL", nullptr_command );
	insertCommandIntoMap( "MOUSEMOTION", nullptr_command );
}

std::shared_ptr<Command> InputHandler::handleInput( SDL_Event& event )
{

	if ( event.type == SDL_KEYDOWN )
	{
		return handleKeys( event );
	}

	if ( ( event.type == SDL_MOUSEMOTION ) || ( event.type == SDL_MOUSEBUTTONDOWN ) || ( event.type == SDL_MOUSEWHEEL ) )
	{
		return handleMouse( event );
	}

	// If nothing was found, return a nullptr.
	return nullptr;
}

std::shared_ptr<Command> InputHandler::handleKeys( SDL_Event& event )
{

	switch ( event.key.keysym.sym )
	{
		case SDLK_a:
			return m_commandMap["A"];

		case SDLK_b:
			return m_commandMap["B"];

		case SDLK_c:
			return m_commandMap["C"];

		case SDLK_d:
			return m_commandMap["D"];

		case SDLK_e:
			return m_commandMap["E"];

		case SDLK_f:
			return m_commandMap["F"];

		case SDLK_g:
			return m_commandMap["G"];

		case SDLK_h:
			return m_commandMap["H"];

		case SDLK_i:
			return m_commandMap["I"];

		case SDLK_j:
			return m_commandMap["J"];

		case SDLK_k:
			return m_commandMap["K"];

		case SDLK_l:
			return m_commandMap["L"];

		case SDLK_m:
			return m_commandMap["M"];

		case SDLK_n:
			return m_commandMap["N"];

		case SDLK_o:
			return m_commandMap["O"];

		case SDLK_p:
			return m_commandMap["P"];

		case SDLK_q:
			return m_commandMap["Q"];

		case SDLK_r:
			return m_commandMap["R"];

		case SDLK_s:
			return m_commandMap["S"];

		case SDLK_t:
			return m_commandMap["T"];

		case SDLK_u:
			return m_commandMap["U"];

		case SDLK_v:
			return m_commandMap["V"];

		case SDLK_w:
			return m_commandMap["W"];

		case SDLK_x:
			return m_commandMap["X"];

		case SDLK_y:
			return m_commandMap["Y"];

		case SDLK_z:
			return m_commandMap["Z"];

		case SDLK_1:
			return m_commandMap["1"];

		case SDLK_2:
			return m_commandMap["2"];

		case SDLK_3:
			return m_commandMap["3"];

		case SDLK_4:
			return m_commandMap["4"];

		case SDLK_5:
			return m_commandMap["5"];

		case SDLK_6:
			return m_commandMap["6"];

		case SDLK_7:
			return m_commandMap["7"];

		case SDLK_8:
			return m_commandMap["8"];

		case SDLK_9:
			return m_commandMap["9"];

		case SDLK_0:
			return m_commandMap["0"];

		case SDLK_F1:
			return m_commandMap["F1"];

		case SDLK_F2:
			return m_commandMap["F2"];

		case SDLK_F3:
			return m_commandMap["F3"];

		case SDLK_F4:
			return m_commandMap["F4"];

		case SDLK_F5:
			return m_commandMap["F5"];

		case SDLK_F6:
			return m_commandMap["F6"];

		case SDLK_F7:
			return m_commandMap["F7"];

		case SDLK_F8:
			return m_commandMap["F8"];

		case SDLK_F9:
			return m_commandMap["F9"];

		case SDLK_F10:
			return m_commandMap["F10"];

		case SDLK_F11:
			return m_commandMap["F11"];

		case SDLK_F12:
			return m_commandMap["F12"];

		case SDLK_LALT:
			return m_commandMap["LALT"];

		case SDLK_RALT:
			return m_commandMap["RALT"];

		case SDLK_LCTRL:
			return m_commandMap["LCTRL"];

		case SDLK_RCTRL:
			return m_commandMap["RCTRL"];

		case SDLK_LSHIFT:
			return m_commandMap["LSHIFT"];

		case SDLK_RSHIFT:
			return m_commandMap["RSHIFT"];

		case SDLK_UP:
			return m_commandMap["UP"];

		case SDLK_DOWN:
			return m_commandMap["DOWN"];

		case SDLK_LEFT:
			return m_commandMap["LEFT"];

		case SDLK_RIGHT:
			return m_commandMap["RIGHT"];

		case SDLK_TAB:
			return m_commandMap["TAB"];

		case SDLK_BACKSPACE:
			return m_commandMap["BACKSPACE"];

		case SDLK_BACKSLASH:
			return m_commandMap["BACKSLASH"];

		case SDLK_CAPSLOCK:
			return m_commandMap["CAPSLOCK"];

		case SDLK_COMMA:
			return m_commandMap["COMMA"];

		case SDLK_PERIOD:
			return m_commandMap["PERIOD"];

		case SDLK_RETURN:
			return m_commandMap["RETURN"];

		case SDLK_QUOTE:
			return m_commandMap["QUOTE"];

		case SDLK_SPACE:
			return m_commandMap["SPACEBAR"];

		case SDLK_DELETE:
			return m_commandMap["DELETE"];

		case SDLK_END:
			return m_commandMap["END"];

		case SDLK_HOME:
			return m_commandMap["HOME"];

		case SDLK_INSERT:
			return m_commandMap["INSERT"];

		case SDLK_BACKQUOTE:
			return m_commandMap["BACKQUOTE"];

		case SDLK_MENU:
			return m_commandMap["MENU"];

		case SDLK_PAGEUP:
			return m_commandMap["PAGEUP"];

		case SDLK_PAGEDOWN:
			return m_commandMap["PAGEDOWN"];

		case SDLK_EQUALS:
			return m_commandMap["EQUALS"];

		case SDLK_MINUS:
			return m_commandMap["MINUS"];

		case SDLK_SEMICOLON:
			return m_commandMap["SEMICOLON"];

		case SDLK_RIGHTBRACKET:
			return m_commandMap["RIGHTBRACKET"];

		case SDLK_LEFTBRACKET:
			return m_commandMap["LEFTBRACKET"];

		case SDLK_SLASH:
			return m_commandMap["SLASH"];
	}

	return nullptr;
}

std::shared_ptr<Command> InputHandler::handleMouse( SDL_Event& event )
{
	switch ( event.type )
	{
		case SDL_MOUSEBUTTONDOWN:
			// Which mouse button was pressed?
			switch ( event.button.button )
			{
				case SDL_BUTTON_LEFT:
					return m_commandMap["LEFT_MOUSE"];

				case SDL_BUTTON_RIGHT:
					return m_commandMap["RIGHT_MOUSE"];

				case SDL_BUTTON_MIDDLE:
					return m_commandMap["MIDDLE_MOUSE"];

				case SDL_BUTTON_X1:
					return m_commandMap["X1_MOUSE"];

				case SDL_BUTTON_X2:
					return m_commandMap["X2_MOUSE"];
			}

			// ERROR 404 cannot find mouse button
			return nullptr;

		case SDL_MOUSEMOTION:
			return m_commandMap["MOUSEMOTION"];

		case SDL_MOUSEWHEEL:
			return m_commandMap["MOUSEWHEEL"];
	}

	// False event signal ABORT!!!
	DEBUG("FALSE EVENT SIGNAL. 'Returning nullptr'");
	return nullptr;
}
















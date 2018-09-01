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

#include <sstream>
#include "management/chunks.hpp"

void ChunkManager::populateChunks( int number )
{
	glm::ivec3 dim = glm::ivec3( 16, 16, 16 );
	for ( int x = 0; x <= number; x++ )
	{
		m_chunks.push_back( randomChunk( dim, glm::ivec3( x, 0, 0 ) ) );
	}
}

Chunk ChunkManager::randomChunk( glm::ivec3 dim, glm::ivec3 pos )
{
	Chunk chunk = Chunk( dim, pos );
	int length = chunk.m_dim.x * chunk.m_dim.y * chunk.m_dim.z;
	for ( int i = 0; i <= length; i++ )
	{
		chunk.m_voxels[i] = ( rand( ) % 2 == 0 );
	}
	return chunk;
}

Chunk ChunkManager::getChunk( glm::ivec3 pos )
{
	for ( Chunk& chunk : m_chunks )
	{
		if ( chunk.m_pos == pos )
		{
			return chunk;
		}
	}

	std::stringstream message;
	message << "Could not find chunk at position: " << pos.x << ", " << pos.y << "," << pos.z;
	WARNING( message.str());

	return Chunk( );
}

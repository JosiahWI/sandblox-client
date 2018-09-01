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

#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "types.hpp"
#include <logging/logging.hpp>


struct Chunk
{

    Chunk() : m_dim(glm::ivec3(16, 16, 16)), m_pos(glm::ivec3(0, 0, 0)) { }

    Chunk(glm::ivec3 dim, glm::ivec3 pos) : m_dim(dim), m_pos(pos) { }

    ~Chunk() { }

    std::vector<bool> m_voxels;
    glm::ivec3 m_dim;
    glm::ivec3 m_pos;
};

class ChunkManager
{
public:

    ChunkManager() { }

    ~ChunkManager() { }

    void populateChunks(int number);
    Chunk randomChunk(glm::ivec3 dim, glm::ivec3 pos);
    Chunk getChunk(glm::ivec3 pos);

private:
    std::vector<Chunk> m_chunks;
};

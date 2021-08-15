#include "Chunk.h"


Chunk::Chunk()
{
    chunk_renderer.init();
    {
        for (unsigned int x = 0; x < CHUNK_WIDTH; x++)
            for (unsigned int y = 0; y < CHUNK_HEIGHT; y++)
                for (unsigned int z = 0; z < CHUNK_LENGTH; z++)
                    blocks[x][y][z] = 0;
    }
}

Chunk::~Chunk() {

}

inline void Chunk::update_mesh() 
{
    mesh.generate_mesh(this);
    chunk_renderer.bufferData(mesh);
    chunk_renderer.bind_layout();
}

void Chunk::render()
{
    chunk_renderer.draw();
}
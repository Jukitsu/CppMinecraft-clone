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

/* Pretty straightforward inline stuff (heck I could have them on the header file)*/
inline const Position &Chunk::get_position() const
{
    return position;
}

inline const BlockID Chunk::get_block(const Vector3D &pos) const
{
    return blocks[(int)pos.x % CHUNK_WIDTH]
                 [(int)pos.y % CHUNK_HEIGHT]
                 [(int)pos.z % CHUNK_LENGTH];
}

inline const BlockID Chunk::get_block(const int x, const int y, const int z) const
{
    return blocks[x % CHUNK_WIDTH]
                 [y % CHUNK_HEIGHT]
                 [z % CHUNK_LENGTH];
}

inline void Chunk::set_block(const Vector3D&pos, BlockID block)
{
    blocks[(int)pos.x % CHUNK_WIDTH]
          [(int)pos.y % CHUNK_HEIGHT]
          [(int)pos.z % CHUNK_LENGTH] = block;
}

inline void Chunk::set_block(const int x, const int y, const int z, BlockID block)
{
    blocks[x % CHUNK_WIDTH]
          [y % CHUNK_HEIGHT]
          [z % CHUNK_LENGTH] = x;
}

/* I might use GL_DYNAMIC_DRAW :p and use bufferSubData instead of bufferData */
inline void Chunk::update_mesh() 
{
    mesh.generate_mesh(this);
    chunk_renderer.bufferData(mesh);
    chunk_renderer.bind_layout();
}

/* shouldn't be that hard to work out what this does */
void Chunk::render()
{
    chunk_renderer.draw();
}
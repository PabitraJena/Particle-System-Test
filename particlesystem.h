#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "raylib.h"

#define MAX_PARTICLES 400

typedef struct Particle {
    Vector2 position;
    Vector2 velocity;

    float rotation;
    float angular_velocity;

    float lifetime;
    float max_lifetime;

    float size;
    float start_size;
    float end_size;

    Color color;
    bool active;
} Particle;

typedef struct ParticleSystem {
    Particle particles[MAX_PARTICLES];
    Texture2D texture;
    float upward_acceleration;
} ParticleSystem;

// Public API
void initialise_system(ParticleSystem *ps, Texture2D texture, float up_accel);
void emit_particles(ParticleSystem *ps, Vector2 position);
void update_particles(ParticleSystem *ps, float dt);
void render_particles(ParticleSystem *ps, int blend_mode);

#endif
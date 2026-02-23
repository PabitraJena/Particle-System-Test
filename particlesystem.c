#include "particlesystem.h"
#include <math.h>
#include <stdlib.h>

float GetRandomFloat(float min, float max) {
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

void initialise_system(ParticleSystem *ps, Texture2D texture, float up_accel){
    ps->texture = texture;
    ps->upward_acceleration = up_accel;

    for (int i = 0; i < MAX_PARTICLES; i++){
        ps->particles[i].active = false;
    }
}

void emit_particles(ParticleSystem *ps, Vector2 position){
    for (int i = 0; i < MAX_PARTICLES; i++){
        if (!ps->particles[i].active){
            Particle *p = &ps->particles[i];

            p->active = true;
            p->position = position;

            float angle = GetRandomFloat(-0.5f, 0.5f);
            float speed = GetRandomFloat(80.0f, 160.0f);

            p->velocity.x = sinf(angle) * speed;
            p->velocity.y = -cosf(angle) * speed;

            p->rotation = GetRandomFloat(0, 360);
            p->angular_velocity = GetRandomFloat(-90, 90);

            p->max_lifetime = GetRandomFloat(0.8f, 1.4f);
            p->lifetime = p->max_lifetime;

            p->start_size = GetRandomFloat(20, 40);
            p->end_size = 0;
            p->size = p->start_size;

            p->color = WHITE;

            break;
        }
    }
}

void update_particles(ParticleSystem *ps, float dt){
    for (int i = 0; i < MAX_PARTICLES; i++){
        Particle *p = &ps->particles[i];

        if (!p->active) continue;

        p->lifetime -= dt;

        if (p->lifetime <= 0){
            p->active = false;
            continue;
        }

        float life_percent = 1.0f - (p->lifetime / p->max_lifetime);

        p->position.x += p->velocity.x * dt;
        p->position.y += p->velocity.y * dt;

        p->velocity.y -= ps->upward_acceleration * dt;

        p->size = p->start_size + (p->end_size - p->start_size) * life_percent;
        p->color.a = (unsigned char)(255 * (1.0f - life_percent));

        p->rotation += p->angular_velocity * dt;
    }
}

void render_particles(ParticleSystem *ps, int blend_mode){
    BeginBlendMode(blend_mode);

    for (int i = 0; i < MAX_PARTICLES; i++){
        Particle *p = &ps->particles[i];
        if (!p->active) continue;

        Rectangle source = {0, 0, ps->texture.width, ps->texture.height};
        Rectangle dest = {p->position.x, p->position.y, p->size, p->size};
        Vector2 origin = {p->size / 2, p->size / 2};

        DrawTexturePro(ps->texture, source, dest, origin, p->rotation, p->color);
    }

    EndBlendMode();
}
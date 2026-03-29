#include "renderer.h"

void renderer_draw_filled_circle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = - radius; h <= radius; h++) {
            if (w*w + h*h <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
}

void renderer_draw_circle_outline(SDL_Renderer *renderer, int cx, int cy, int radius, int thickness) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            int distance_squared = w*w + h*h;
            int outer_radius_squared = radius * radius;
            int inner_radius_squared = (radius - thickness) * (radius - thickness);
            if (distance_squared <= outer_radius_squared && distance_squared >= inner_radius_squared) {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
}

void renderer_draw_ball(SDL_Renderer *renderer, const Ball *ball) {
    // Black outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    renderer_draw_circle_outline(renderer, ball->x, ball->y, ball->radius + 2, 3);
    
    // Big circle
    SDL_SetRenderDrawColor(renderer, ball->r, ball->g, ball->b, 255);
    renderer_draw_filled_circle(renderer, ball->x, ball->y, ball->radius);

    // Shiny highlight effect - blend with white for realistic shine
    int highlight_r = ball->r + (255 - ball->r) * 0.7;  // Move 70% toward white
    int highlight_g = ball->g + (255 - ball->g) * 0.7;
    int highlight_b = ball->b + (255 - ball->b) * 0.7;
    
    // Ensure values don't exceed 255
    highlight_r = highlight_r > 255 ? 255 : highlight_r;
    highlight_g = highlight_g > 255 ? 255 : highlight_g;
    highlight_b = highlight_b > 255 ? 255 : highlight_b;
    
    SDL_SetRenderDrawColor(renderer, highlight_r, highlight_g, highlight_b, 180);
    renderer_draw_filled_circle(renderer, ball->x - ball->radius/3, ball->y - ball->radius/3, ball->radius/4);
}

void renderer_draw_balls(SDL_Renderer *renderer, const Ball balls[], int count) {
    for (int i = 0; i < count; i++){
        renderer_draw_ball(renderer, &balls[i]);
    }
}

void renderer_draw_filled_heart(SDL_Renderer *renderer, int x, int y, int size) {
    // Draw two circles for the top of the heart
    renderer_draw_filled_circle(renderer, x - size/4, y, size/4);
    renderer_draw_filled_circle(renderer, x + size/4, y, size/4);

    // Draw a triangle for the bottom
    // Fill triangle (approximate by drawing lines)
    for (int i = 0; i < size/2; i++) {
        int px1 = x - size/2 + i;
        int px2 = x + size/2 - i;
        int py = y + i;
        SDL_RenderDrawLine(renderer, px1, py, px2, py);
    }
}

void renderer_draw_platform(SDL_Renderer *renderer, const Platform *platform){
    // Black outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect outline_rect = {
        platform->x - 2,
        platform->y + platform->bendOffset - 2,
        platform->width + 4,
        platform->height - platform->bendOffset + 4
    };
    SDL_RenderFillRect(renderer, &outline_rect);
    
    // Cyan platform
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Cyan
    // Simulate bend
    SDL_Rect rect = {
        platform->x,
        platform->y + platform->bendOffset,
        platform->width,
        platform->height - platform->bendOffset
    };
    SDL_RenderFillRect(renderer, &rect);
}
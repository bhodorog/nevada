#include <stdio.h>
#include <stdlib.h>
#include "textures.h"



void renderTexture(Texture* t, SDL_Game* game, SDL_Rect* clip, int x, int y, int width, int height);
Texture* loadSpriteSheet(const char* fileName, SDL_Game* game, unsigned short spriteWidth, unsigned short spriteHeigth);
void freeTexture(Texture* t);
void nextFrame(Texture* t);

SDL_Rect* getSpriteCR(Texture* t, int x, int y, int width, int height);
SDL_Rect* getSpriteI(Texture* t, int index, int width, int height);

SDL_Rect* createRectsForSprites(Level* level, const short size, Texture* t);





void freeTexture(Texture* t) {
    if (t->mTexture != NULL) {
        SDL_DestroyTexture(t->mTexture);
        t->mTexture = NULL;
        free(t);
    }
}


void renderTexture(Texture* t, SDL_Game* game, SDL_Rect* clip, int x, int y, int width, int height) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(game->gRenderer, t->mTexture, clip, &renderQuad);
}

Texture* loadSpriteSheet(const char* fileName, SDL_Game* game, unsigned short spriteWidth, unsigned short spriteHeigth) {
    Texture* t = malloc(sizeof(Texture));
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(fileName);
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", fileName, IMG_GetError());
        t = NULL;
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(game->gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", fileName, SDL_GetError());
        } else {
            t->width = loadedSurface->w;
            t->height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    t->mTexture = newTexture;
    t->sWidth = spriteWidth;
    t->sHeight = spriteHeigth;
    return t;
}


void nextFrame(Texture* t) {

}

SDL_Rect* getSpriteXY(Texture* t, int x, int y, int width, int height) {
    SDL_Rect* r = malloc(sizeof(SDL_Rect));
    r->x = x * width;
    r->y = y * height;
    r->w = width;
    r->h = height;
    return r;
}

SDL_Rect* getSpriteI(Texture* t, int index, int width, int height) {
    SDL_Rect* r = malloc(sizeof(SDL_Rect));
    int col = t->width / width;
    //int row = t->height / height;
    r->x = (index % col) * width;
    r->y = (index / col) * height;
    //printf("Cols: %i, Rows: %i, index:%i, x:%i, y:%i, w:%i, h:%i\n", col, row, index, r->x, r->y, width, height);
    r->w = width;
    r->h = height;
    return r;
}

SDL_Rect* createRectsForSprites(Level* level, const short size, Texture* t) {
    SDL_Rect* l = malloc(sizeof(SDL_Rect) * size);
    for (int i = 0; i < level->size; i++)
        l[i] = *getSpriteI(t, level->content[i], t->sWidth, t->sHeight);
    return l;
}

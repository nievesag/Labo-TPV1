#include "checkML.h"


#include "GameObject.h"
#include "GameState.h"
#include "PlayState.h"

GameObject::GameObject(GameState* game) : game(game), application(game->getApplication()){};

GameObject::GameObject(PlayState* game) : game(game) {};

GameObject::~GameObject() {}

void GameObject::render() const {}

void GameObject::update() {}

void GameObject::save(ostream& out) const {}
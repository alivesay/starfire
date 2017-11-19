#ifndef SCENE_H
#define SCENE_H

#include "list.h"

class SceneNode {
  public:
    SceneNode() : _parent(NULL) { }

    virtual ~SceneNode() {
      this->destroy();
    }

    void release() {
      delete this;
    }

    virtual void updateChildren() {
      for (List<SceneNode*>::ListNode* i = this->_children.begin(); i; i = i->next) {
        i->data->update();
      }
    }

    virtual void renderChildren() {
      for (List<SceneNode*>::ListNode* i = this->_children.begin(); i; i = i->next) {
        i->data->render();
      }
    }

    virtual void update() {
      this->updateChildren();
    }

    virtual void render() {
      this->renderChildren();
    }

    void destroy() {
      for (List<SceneNode*>::ListNode* i = this->_children.begin(); i; i = i->next) {
        i->data->release();
      }

      this->_children.clear();
    }

    void addNode(SceneNode* node) {
      node->setParent(this);
      this->_children.pushFront(node);
    }

    void setParent(SceneNode* node) {
      this->_parent = node;
    }

  private:
    List<SceneNode*> _children;
    SceneNode* _parent;
};

#endif // SCENE_H

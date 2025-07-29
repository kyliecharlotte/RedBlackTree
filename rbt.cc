#include "rbt.h"
#include <typeinfo>

// DELETE

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}

// New functions to RBT

// Right rotate - CLRS
void RBT::right_rotate(RBTNode* y)
{
	RBTNode * left_x = (RBTNode*) y->get_left();
	RBTNode * right_x = (RBTNode*) left_x->get_right();
	RBTNode * parent = (RBTNode*) y->get_parent();
		
	y->add_left(right_x);
		
        if (right_x != sentinel && right_x != nullptr) {
                right_x->add_parent(y);
        };

	left_x->add_parent(parent);

        if (parent == sentinel) {
                root = left_x;
		((RBTNode*) root)->add_color(BLACK);
        } else if (y == parent->get_right()) {
                parent->add_right(left_x);
        } else {
                parent->add_left(left_x);
        }

        left_x->add_right(y);
        y->add_parent(left_x); 
}

// Left rotate - CLRS
void RBT::left_rotate(RBTNode* x)
{

	RBTNode * right_x = (RBTNode*)x->get_right();
        RBTNode * left_x = (RBTNode*)right_x->get_left();
        RBTNode * parent = (RBTNode*)x->get_parent();

        x->add_right(left_x);
		
        if ((left_x != sentinel) && (left_x != nullptr)) {
		((RBTNode*)(left_x))->add_parent(x);
        };
	
        ((RBTNode*)(right_x))->add_parent(parent);

        if (parent == sentinel) {
                root = right_x;
		((RBTNode*)root)->add_color(BLACK);

        } else if (x == parent->get_left()) {
                parent->add_left(right_x);
        } else {
                parent->add_right(right_x);
        }
        right_x->add_left(x);
        x->add_parent(right_x);

}

// Insert fixup - CLRS
void RBT::rb_insert_fixup(RBTNode* in)
{
	RBTNode* y_node;
	RBTNode* parent = ((RBTNode*) in->get_parent());
	RBTNode* grandparent = ((RBTNode*) parent->get_parent());
	RBTNode* current = in;

	// Loop runs while parent is red
	while (((RBTNode*)(current->get_parent()))->get_color() == RED) {
		
		parent = (RBTNode*)current->get_parent();
		grandparent = (RBTNode*)parent->get_parent();
		
		// IF parent is left child
		if (parent == grandparent->get_left()) {
			y_node = (RBTNode*) grandparent->get_right();

			if (y_node->get_color() == RED) {
				parent->add_color(BLACK);
				y_node->add_color(BLACK);
				grandparent->add_color(RED);
				current = grandparent;
			} else {
				if (current == parent->get_right()) {
				current = parent;
				left_rotate(current);
   	                        parent = ((RBTNode*)(current->get_parent()));
          	                grandparent = ((RBTNode*)(parent->get_parent()));
				}

			parent->add_color(BLACK);
			grandparent->add_color(RED);
			right_rotate(grandparent);
			}
		// ELSE parent is right child
		} else {

			y_node = ((RBTNode*)(grandparent->get_left()));
                        if (y_node->get_color() == RED) {
                                parent->add_color(BLACK);
                                y_node->add_color(BLACK);
                                grandparent->add_color(RED);
                                current = grandparent;

                        } else {
                                if (current == parent->get_left()) {
                                current = parent;
                                right_rotate(current);
                                parent = (RBTNode*)current->get_parent();
                        	grandparent = (RBTNode*)current->get_parent();
				}

                        parent->add_color(BLACK);
                        grandparent->add_color(RED);
                        left_rotate(grandparent);
                        }
		
		}

	}
	// Set root to black
	((RBTNode*)root)->add_color(BLACK);
	
}

// RBT insert - Lecture Notes / BST
void RBT::rb_insert_node(RBTNode* in)
{
	// BST algorithm, sentinel and color checks
	
	// Code from BST
	RBTNode* tmp = sentinel;
    	RBTNode* cur = (RBTNode*)(root);
    	while(cur != sentinel) {
        	tmp = cur;
        if(in->get_key() <= cur->get_key()) {
            cur = ((RBTNode*)cur->get_left());
        } else {
            cur = ((RBTNode*)cur->get_right());
        }
    	}
    	in->add_parent(tmp);
    	if (tmp == sentinel) {
        	root = in;
    	} else {
        if(in->get_key() <= tmp->get_key()) {
            tmp->add_left(in);
        } else {
            tmp->add_right(in);
        }
    }
	
	// Sentinel checks
	in->add_left(sentinel);
	((RBTNode*)in->get_left())->add_color(BLACK);
	in->add_right(sentinel);
	((RBTNode*)in->get_right())->add_color(BLACK);
	in->add_color(RED);
	if (in->get_parent() == nullptr) {
		in->add_parent(sentinel);
		in->add_color(BLACK);
	}
	rb_insert_fixup(in);

}

// delete fixup - CLRS
void RBT::rb_delete_fixup(RBTNode* in)
{
	RBTNode* w;
	RBTNode * in_parent;
	
	// Loop runs while current node is not root and color is black
	while (in != root && in->get_color() == BLACK) {
		
		in_parent = (RBTNode*)in->get_parent();
	
		// IF parent is left child
		if (in == ((RBTNode*)in->get_parent()->get_left())) {
			w = (RBTNode*)in_parent->get_right();
				
			if (w != sentinel && w->get_color() == RED) {	
				w->add_color(BLACK);
				in_parent->add_color(RED);
				left_rotate(in_parent);
				w = (RBTNode*) in_parent->get_right();
			}
			Node_color w_right;
                        Node_color w_left;
                        
			if (w == sentinel || w == nullptr || w->get_right() == sentinel) {
                                w_right = BLACK;
                        } else {
                                w_right = ((RBTNode*)w->get_right())->get_color();
                        }
			
                        if (w->get_left() == sentinel || w == sentinel || w == nullptr) {
                                w_left = BLACK;
                        } else {
                                w_left = ((RBTNode*)w->get_left())->get_color();
                        }
			if (w_right == BLACK && w_left == BLACK) {
	
				((RBTNode*) w)->add_color(RED);
				in = in_parent;
				} else {
				
				if (((RBTNode*)w->get_right())->get_color() == BLACK) {
					((RBTNode*)w->get_left())->add_color(BLACK);
					w->add_color(RED);
					right_rotate(w);
					w = (RBTNode*) in_parent->get_right();
				}
				((RBTNode*)w)->add_color(((RBTNode*)(in_parent))->get_color());
				((RBTNode*)in_parent)->add_color(BLACK);
				((RBTNode*)w->get_right())->add_color(BLACK);
				left_rotate(in_parent);
				in = (RBTNode*) root;
			}

		// ELSE parent is right child
		} else {
			w = (RBTNode*)in_parent->get_left();
			Node_color w_color;
			
			if (w == sentinel || w == nullptr) {
				w_color = BLACK;
			} else {
				w_color = w->get_color();
			}
		
                        if (w_color == RED) {
				w->add_color(BLACK);
				((RBTNode*)in_parent)->add_color(RED);

				right_rotate(in_parent);
                                w = (RBTNode*) in->get_parent()->get_left();
				
                        }
			Node_color w_right;
			Node_color w_left;
			if (w == sentinel || w->get_right() == sentinel || w == nullptr) {
				w_right = BLACK;
			} else {
				w_right = ((RBTNode*)w->get_right())->get_color();
			}

			if (w == sentinel || w->get_left() == sentinel || w == nullptr) {
                                w_left = BLACK;
                    
			} else {
                                w_left = ((RBTNode*)w->get_left())->get_color();
                        }

			if ((w_right == BLACK) && (w_left == BLACK)) {
				((RBTNode*)w)->add_color(RED);
                                in = in_parent;
                        } else {
                                if (((RBTNode*)w->get_left())->get_color() == BLACK) {
                                        ((RBTNode*)w->get_right())->add_color(BLACK);
                                        w->add_color(RED);
                                        left_rotate(w);
                                        w = (RBTNode*) in_parent->get_left();
                                }
                                w->add_color(((RBTNode*)in_parent)->get_color());
                                ((RBTNode*)(in_parent))->add_color(BLACK);
                                ((RBTNode*)w->get_left())->add_color(BLACK);
                                right_rotate(in_parent);
                                in = (RBTNode*) root;
			}
		}
	}
	// Set final in color to black
	in->add_color(BLACK);}

// delete node - CLRS / Help Hours
void RBT::rb_delete_node(RBTNode* out)
{
	RBTNode* y = out;
	RBTNode* x;
	Node_color original_color = y->get_color();
	
	if ((out->get_left()) == nullptr) {
		out->add_left(sentinel);
		((RBTNode*)out->get_left())->add_color(BLACK);
	}	
	if ((out->get_right()) == nullptr) {
		out->add_right(sentinel);
		((RBTNode*)out->get_right())->add_color(BLACK);
	}
	if ((out->get_parent()) == nullptr) {
		out->add_parent(sentinel);
		((RBTNode*)out->get_parent())->add_color(BLACK);
	}

	// IF left child does not exist
	if ((out->get_left()) == sentinel) {
	
		x = (RBTNode*)out->get_right();
		transplant(out,x);

	// ELSE IF right child does not exist
	} else if (out->get_right() == sentinel) {
	
		x = (RBTNode*)out->get_left();
		transplant(out, x);

	// ELSE exist children
	} else {
		
		RBTNode* cur = (RBTNode*) out->get_right();
   		
		while(((RBTNode*)cur->get_left()) != sentinel) {

		 	 cur = (RBTNode*) cur->get_left();
    		}

		y = cur; 	
		original_color = y->get_color();
		x = (RBTNode*) y->get_right();	
		
		if (out == y->get_parent()) {;
			x->add_parent(y);
		
		} else {
			transplant(y, x);	
			y->add_right(out->get_right());
			out->get_right()->add_parent(y);
			((RBTNode*)y->get_right())->add_parent(y);
		}
		
		transplant(out, y);

		if (y != out->get_left()){
			y->add_left(out->get_left());
			(out->get_left())->add_parent(y);
		}
		y->add_color(out->get_color());
	}
	delete(out); // free out
	if (original_color == BLACK) {	
		rb_delete_fixup(x);
	}
}

// ---------------------------------------

// Helper function: transplant
void RBT::transplant(RBTNode* u, RBTNode* v) {
	// Transplant two nodes u, v based on relationship
	if (u->get_parent() == sentinel) {
		root = v;
		
		if (u->get_right() != v) {
		((RBTNode*)root)->add_right(u->get_right());
               	((RBTNode*)root->get_right())->add_parent(root);
		}

		if (u->get_left() != v) {
		((RBTNode*)root)->add_left(u->get_left());
		((RBTNode*)root->get_left())->add_parent(root);
		}
		
		if (v != nullptr) {
			v->add_parent(sentinel);
		}

	} else if (u == ((RBTNode*)(u->get_parent()->get_left()))) {
		((RBTNode*)u->get_parent())->add_left(v);	
		
	} else {
		((RBTNode*)u->get_parent())->add_right(v);
		
	} 
	
	v->add_parent(u->get_parent());
}


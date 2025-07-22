#ifndef LABEL_H
#define LABEL_H

#include "EText.h"
#include <memory>
#include "Leaf.h"

class Label : public Leaf
{

public:
	Label(string initialText, Vector2f origin, Vector2f siz);
private:
	unique_ptr<EText> text; // Pointer to the EText object for label text
};


#endif // !LABEL_H

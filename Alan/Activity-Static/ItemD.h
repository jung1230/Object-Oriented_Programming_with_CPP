#ifndef ITEMD_H_
#define ITEMD_H_

#include "Item.h"

class ItemD : public Item {
public:
    ItemD(int, float);
    ItemD();
    ItemD(const ItemD&);
    virtual ~ItemD();
    static int getNumberOfItemsD();

private:
    static int numberOfItemsD;
};

#endif /* ITEMD_H_ */

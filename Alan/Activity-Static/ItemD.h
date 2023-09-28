#ifndef ITEMD_H_
#define ITEMD_H_
#include "Item.h"


class ItemD : public Item{
public:
   ItemD(int, float);
   ItemD( );
   ItemD (const Item&);
   virtual ~ItemD( );
   virtual void print( );
   static int getNumberOfItems( );

private: // "private" to make explicit
   static int derivednumberOfItems;
   int itemNum;
   float price;
};
#endif /* ITEM_H_ */


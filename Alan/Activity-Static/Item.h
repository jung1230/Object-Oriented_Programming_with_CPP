#ifndef ITEM_H_
#define ITEM_H_
class Item {
public:
   Item(int, float);
   Item( );
   Item (const Item&);
   virtual ~Item( );
   virtual void print( );
   static int getNumberOfItems( );

private: // "private" to make explicit
   static int numberOfItems;
   int itemNum;
   float price;
};
#endif /* ITEM_H_ */


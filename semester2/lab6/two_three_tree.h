#pragma once


#include <iostream>
#include "point.h"


using Lambda = std::function<void(Point&)>;


struct two3node
{
    Point k1,k2;
    two3node* left;
    two3node* middle;
    two3node* right;
    int n;
};


struct usefulData{
    Point midValue;
    two3node* child;

    usefulData(){
        child = nullptr;
    }


    usefulData (two3node* c){
        child = c;
    }


    usefulData (two3node* c, Point m)
    {
        child    = c;
        midValue = m;
    }


    usefulData& operator = (const usefulData & otherusefulData)
    {
        if (&otherusefulData != this)
        {
            child    = otherusefulData.child;
            midValue = otherusefulData.midValue;
        }

        return *this;
    }

    usefulData& operator = (usefulData && otherusefulData) noexcept
    {
        if (&otherusefulData != this)
        {
            child    = otherusefulData.child;
            midValue = otherusefulData.midValue;
        }

        return *this;
    }


    usefulData(usefulData & otherusefulData)
    {
        child = otherusefulData.child;
        midValue = otherusefulData.midValue;
    }
};


class two3Tree{

private:
    two3node * root;

public:
    two3Tree()
    {
        root = nullptr;
    }


    ~two3Tree()
    {
        if (root != nullptr)                   //If tree is empty then do nothing.
        {
            destroy(root);
        }
    }


    void destroy (two3node * r)
    {
        if (r != nullptr)
        {
            destroy (r -> left);
            destroy (r -> middle);
            destroy (r -> right);
            delete r;
        }
    }


    int isRotationPossible(two3node* p, two3node* r)
    {
        if (p != r)     //p will be equal to r only once when r is the root.
        {
            if (p -> n == 1)    //Parent is a 2 node
            {
                //If UNDERFLOW had occured at r
                if( r -> n == 0 )
                {
                    if ( (p -> left == r) && (p -> middle -> n == 2) )  //If deficiency was occured on left child
                        return 2;           // 2 indicates anti-clockwise(left) rotation is to be done

                    else if ( (p -> middle == r) && ( p -> left -> n == 2) )    //If deficiency was occured on middle child
                        return 1;           // 1 indicates clockwise(right) rotation is to be done
                }

                    //If OVERFLOW had occured at r
                else
                {
                    if (! ((p -> left -> n == 2) && (p -> middle -> n == 2)))   //One has to be a 2 node and other a 3 node
                    {
                        if (p -> left == r)
                            return 1;            // 1 indicates clockwise(right) rotation is to be done

                        else
                            return 2;             // 2 indicates anti-clockwise(left) rotation is to be done
                    }
                }
            }


            else                //Parent is a 3 node
            {
                if (r -> n == 0)    //If UNDERFLOW had occurred at r
                {
                    if ( (p -> left == r) && (p -> middle -> n == 2) )  //If deficiency is created on left child
                    {
                        return 2;   // 2 indicates anti-clockwise(left) rotation is to be done
                    }

                    else if (p -> middle == r)      //If deficiency is created on middle child
                    {
                        if (p -> left -> n == 2)
                            return 1;           // 1 indicates clockwise(right) rotation is to be done

                        else if (p -> right -> n == 2)
                            return 2;           // 2 indicates anti-clockwise(left) rotation is to be done
                    }

                    else                    //If deficiency is created on right child
                    {
                        if ( p -> middle -> n == 2)
                            return 1;         // 1 indicates clockwise(right) rotation is to be done
                    }
                }


                else                //If OVERFLOW had occured at r
                {
                    if ( (p -> left == r) && (p -> middle -> n == 1) )
                        return 1;          // 1 indicates clockwise(right) rotation is to be done


                    else if (p -> middle == r)
                    {
                        if (p -> left -> n == 1)
                            return 2;           // 2 indicates anti-clockwise(left) rotation is to be done

                        else if (p -> right -> n == 1)
                            return 1;           // 1 indicates clockwise(right) rotation is to be done
                    }

                    else
                    {
                        if (p -> middle -> n == 1)
                            return 2;           // 2 indicates anti-clockwise(left) rotation is to be done
                    }
                }
            }
        }

        return 0;   //No rotation
    }


    usefulData rotateRight (two3node* p, two3node* r, Point d, two3node* child)
    {

        //CASE 1 :  If the rotation is done to overcome the UNDERFLOW at r
        if (r -> n == 0)
        {
            if ( (p -> n == 2) && ( p -> right == r) )       //If parent is a 3 node and deficiency is created on its right child
            {
                r -> k1 = p -> k2;              //Separator Key
                r -> n = 1;

                p -> k2 = p -> middle -> k2;

                p -> middle -> n = 1;

                //Updating Pointers

                p -> right -> left = p -> middle -> right;

            }

            else    //If the deficiency was created at middle node then the processing is the same irrespective of the fact
                //whether the parent was a 2 node or a 3 node
            {
                r -> k1 = p -> k1;              //Separator Key
                r -> n = 1;                     //Because one key was moved into r

                p -> k1 = p -> left -> k2;

                p -> left -> n = 1;

                //Updating Pointers

                p -> middle -> left = p -> left -> right;
            }
        }


            //CASE 2 :  If the rotation is done to overcome the OVERFLOW at r
        else
        {
            if ( p -> n == 2 && p -> middle == r )      //If parent is a 3 node and p->middle is also a 3 node
            {
                p -> right -> k2 = p -> right -> k1;    //Right node ney ab 2 se 3 banna hai. Is lye k1 ko shift left kar rahey kiun
                //ke K1 pe ab parent se aik key ne ana hai.

                p -> right -> k1 = p -> k2;             //Separator Key

                if (d < r -> k1)
                {
                    p -> k2 = r -> k2;
                    r -> k2 = r -> k1;
                    r -> k1 = d;
                }

                else if (d < r -> k2)
                {
                    p -> k2 = r -> k2;
                    r -> k2 = d;
                }

                else
                {
                    p -> k2 = d;
                }


                p -> right -> right  = p -> right  -> middle;
                p -> right -> middle = p -> right -> left;

                p -> right -> left   = child;

                p -> right -> n = 2;
            }

            else    //if r is the left node then the processing is same irrespective of the fact whether the parent is a 2 or 3 node
            {
                p -> middle -> k2 = p -> middle -> k1;  //Middle node ney ab 2 se 3 banna hai. Is lye k1 ko shift left kar rahey kiun
                //ke K1 pe ab parent se aik key ne ana hai.
                p -> middle -> k1 = p -> k1;

                if (d < r -> k1)
                {
                    p -> k1 = r -> k2;
                    r -> k2 = r -> k1;
                    r -> k1 = d;
                }

                else if (d < r -> k2)
                {
                    p -> k1 = r -> k2;
                    r -> k2 = d;
                }

                else
                {
                    p -> k1 = d;
                }

                p -> middle -> right = p -> middle -> middle;
                p -> middle -> middle = p -> middle -> left;

                p -> middle -> left   = child;

                p -> middle -> n = 2;
            }
        }

        return (nullptr);
    }


    usefulData rotateLeft (two3node* p, two3node* r, Point d, two3node* child)
    {

        /*CASE 1 :  If the rotation is done to overcome the UNDERFLOW at r*/
        if ( r -> n == 0)
        {
            if ( (p -> n == 2) && ( p -> middle == r) ) //If the parent is a 3 node and if the deficiency is created at middle node
            {
                r -> k1 = p -> k2;                  //Separator Key
                r -> n = 1;

                p -> k2 = p -> right -> k1;

                p -> right -> k1 = p -> right -> k2;
                p -> right -> n = 1;

                //Updating Pointers
                p -> middle -> middle = p -> right -> left;

                p -> right -> left   = p -> right -> middle;
                p -> right -> middle = p -> right -> right;
            }

            else        //If the deficiency was created at left node then the processing is the same irrespective of the fact
                //whether the parent was a 2 node or a 3 node
            {
                r -> k1 = p -> k1;                  //Separator Key
                r -> n = 1;

                p -> k1 = p -> middle -> k1;

                p -> middle -> k1 = p -> middle -> k2;
                p -> middle -> n  = 1;

                //Updating Pointers
                p -> left -> middle = p -> middle -> left;

                p -> middle -> left   = p -> middle -> middle;
                p -> middle -> middle = p -> middle -> right;
            }

        }


            /*CASE 2 :  If the rotation is done to overcome the OVERFLOW at r*/
        else
        {
            if ( p -> n == 2 && p -> right == r )       //If parent is a 3 node and p->right is also a 3 node
            {
                p -> middle -> k2 = p -> k2;                //Separator Key

                if (d < r -> k1)
                {
                    p -> k2 = d;
                }

                else if (d < r -> k2)
                {
                    p -> k2 = r -> k1;
                    r -> k1 = d;
                }

                else
                {
                    p -> k2 = r -> k1;
                    r -> k1 = r -> k2;
                    r -> k2 = d;
                }

                p -> middle -> right = p -> right -> left;

                p -> right -> left  = p -> right -> middle;
                p -> right -> middle = p -> right -> right;
                p -> right -> right = child;

                p -> middle -> n = 2;
            }

            else    //if r is the middle node then the processing is same irrespective of the fact whether the parent is a 2 or 3 node
            {
                p -> left -> k2 = p -> k1;      //Separator Key

                if (d < r -> k1)
                {
                    p -> k1 = d;
                }

                else if (d < r -> k2)
                {
                    p -> k1 = r -> k1;
                    r -> k1 = d;
                }

                else
                {
                    p -> k1 = r -> k1;
                    r -> k1 = r -> k2;
                    r -> k2 = d;
                }

                p -> left -> right = p -> middle -> left;

                p -> middle -> left  = p -> middle -> middle;
                p -> middle -> middle = p -> middle -> right;
                p -> middle -> right = child;

                p -> left -> n = 2;
            }
        }

        return (nullptr);
    }


    void add(Point d){

        two3node* p = root;                  //Parent Pointer (Will be used for rotation purposes)

        usefulData s1 = insert(root, d, p);

        if (s1.child != nullptr){               //The case when the result of the split reaches the root and root itself is to be splitted
            two3node * temp = new two3node;

            temp -> k1 = s1.midValue;
            temp -> n  = 1;

            temp -> left = root;
            temp -> middle  = s1.child;

            temp -> right = nullptr;
            root = temp;
        }


    }


    usefulData insert (two3node* & r, Point d, two3node* p){
        //Case 1 (Empty Tree)
        if( r == nullptr)               //Tree is completely Empty (This case happens once in the lifetime of a tree!)
        {
            two3node* temp = new two3node;

            temp -> k1 = d;
            temp -> left = temp -> middle = temp -> right = nullptr;

            temp -> n = 1;
            r = temp;

            return (nullptr);
        }


            //Case 2 (Leaf Nodes)
        else if (r -> left == nullptr)  //r is a leaf node
        {
            if ( r -> n == 1)           //r is a 2 node and hence data can be accomodated
            {
                //Simple Data Accomodation
                if ( d < r -> k1)
                {
                    r -> k2 = r -> k1;
                    r -> k1 = d;
                }

                else
                    r -> k2 = d;

                r -> n = 2;

                return (nullptr);
            }


            else                        //r is a 3 node so overflow as a result
            {
                // If rotation is not possible then try split

                usefulData s1;


                int e = isRotationPossible(p,r);

                if (e == 1)
                    s1 = rotateRight(p,r,d, nullptr);

                else if (e == 2)
                    s1 = rotateLeft(p,r,d, nullptr);

                else
                    s1 = split3node(r, d, nullptr);        //Splitting is to be done if the rotation didn't work

                return s1;
            }
        }


            //Case 3 (Non-Leaf Nodes)
        else                            //r is a non-leaf node
        {
            if ( r -> n == 1)           //r is a 2 node
            {
                if (d <= r -> k1)
                {
                    usefulData s1 = insert (r -> left, d, r);

                    //Because parents par splitting ka result pass on hota hai
                    if (s1.child != nullptr)
                    {
                        //Larger key ko right pe shift kar do, isi lye ye do steps
                        r -> k2 = r -> k1;
                        r -> k1 = s1.midValue;

                        r -> right = r -> middle;
                        r -> middle = s1.child;

                        r -> n = 2;
                    }
                }

                else if (d > r -> k1)
                {
                    usefulData s1 = insert (r -> middle, d, r);

                    //Because parents par splitting ka result pass on hota hai
                    if (s1.child != nullptr)
                    {
                        //key ko shift karne ki zaroorat nai pari, isi lye oper wale case mai kye gaye do steps yahan nahi kye

                        r -> k2 = s1.midValue;
                        r -> right = s1.child;

                        r -> n = 2;
                    }
                }

                return (nullptr);
            }


            else                            //r is a 3 node
            {
                usefulData s1;

                if ( d <= r -> k1)
                    s1 = insert (r -> left, d, r);

                else if (d <= r -> k2)
                    s1 = insert (r -> middle, d, r);

                else
                    s1 = insert (r -> right, d, r);


                //In case oper waley teen cases mai se kisi case mai splitting huwi ho. Ab us splitting waley data ko
                //yahan accomodate karna
                if (s1.child != nullptr)
                {

                    // If rotation is not possible then try split

                    int e = isRotationPossible(p ,r);

                    if (e == 1)
                        s1 = rotateRight(p ,r ,s1.midValue, s1.child);

                    else if (e == 2)
                        s1 = rotateLeft(p ,r ,s1.midValue, s1.child);

                    else
                        s1 = split3node(r, s1.midValue, s1.child);      //Splitting is to be done if the rotation didn't work

                    return s1;
                }

                return (nullptr);
            }
        }

    }


    usefulData split3node (two3node* current, Point k, two3node* child)
    {
        //Child means that child which was made orphan in the previous split operation

        Point mid;

        two3node* temp = new two3node;
        temp -> n = 1;

        temp -> left = temp -> middle = temp -> right = nullptr;


        if (k < current -> k1)
        {
            mid = current -> k1;

            temp -> k1    = current -> k2;
            current -> k1 = k;

            if (current -> left != nullptr)
            {
                temp -> left = current -> middle;
                temp -> middle = current -> right;
                current -> middle = child;
            }
        }


        else if (k < current -> k2)
        {
            mid = k;

            temp -> k1    = current -> k2;

            if (current -> left != nullptr)
            {
                temp -> left = child;
                temp -> middle = current -> right;
            }
        }

        else
        {
            mid = current -> k2;

            temp -> k1 = k;

            if(current -> left != nullptr)
            {
                temp -> left = current -> right;
                temp -> middle = child;
            }
        }

        current -> right = nullptr;
        current -> n = 1;

        usefulData s1(temp, mid);
        return s1;
    }


    usefulData merge(two3node* p, two3node* &r, two3node* child)
    {

        if( (p -> n == 2) && (p -> right == r) ) //If parent is a 3 node and deficiency is created on right of parent
        {
            p -> middle -> k2 = p -> k2;

            p -> middle -> n  = 2;

            p -> middle -> right = child;

            child = nullptr;
        }

        else            //If deficiency is created on left or middle child, then the processing is (mostly) the same (just a few checks only)
            //irrespective of the fact that whether parent is a 2 node or a 3 node

        {
            if (p -> left == r)    //Deficiency is created on left child
            {
                p -> middle -> k2 = p -> middle -> k1;      //Shifting K1 to K2's position
                p -> middle -> k1 = p -> k1;

                p -> middle -> n = 2;

                //Updating children of the node where merge is done because now it has become a 3 node
                p -> middle -> right = p -> middle -> middle;
                p -> middle -> middle = p -> middle -> left;
                p -> middle -> left  = child;

                child = p -> middle;

                p -> left   = p -> middle;
                p -> middle = p -> right;
            }

            else                    //Deficiency is created on middle child
            {
                p -> left -> k2 = p -> k1;

                p -> left -> n = 2;

                p -> left -> right = child;

                child = p -> left;

                p -> middle = p -> right;
            }

            if (p -> n == 2)
            {
                p -> k1 = p -> k2;      //Shift k2 to k1
                child  = nullptr;
            }
        }


        p -> right = nullptr;

        p -> n--;       //Because one key was moved from parent to its child. So one key is decreased.


        //Deleting the node where the deficieny was created
        r -> left = r -> middle = r -> right = nullptr;
        delete r;
        r = nullptr;


        return (child);
    }


    void deleteNode (Point d){
        two3node * p = root;     //Parent pointer will be used for rotation and merging purposes

        Delete(root,d,p);
    }


    usefulData Delete(two3node* r , Point d, two3node* p){
        if (r != nullptr)                      //When Tree is empty, do nothing
        {

            /*-------------------------Cases-----------------------*/

            //CASE 1 when key from intermediate node is to be deleted

            if (r -> left != nullptr)          //Non-Leaf Node , Swap with predecessor
            {

                usefulData s1(nullptr);

                if (r -> n == 1)    //2 node
                {
                    if (d != r -> k1)
                    {
                        if (d < r -> k1)
                        {
                            s1 = Delete (r -> left, d, r);
                        }

                        else
                            s1 = Delete (r -> middle, d, r);

                        if(s1.child == nullptr)
                            return s1;
                    }
                }


                else                //3 node
                {
                    if ( (d != r -> k1) && ( d != r -> k2) )
                    {
                        if (d < r -> k1)
                        {
                            s1 = Delete (r -> left, d, r);
                        }

                        else if (d < r -> k2)
                        {
                            s1 = Delete (r -> middle, d, r);
                        }

                        else
                            s1 = Delete (r -> right, d, r);

                        if(s1.child == nullptr)
                            return s1;
                    }
                }


                if(root -> n == 0)  //When the root itself is merged. So new root is formed
                {
                    root -> left = root -> middle = root -> right = nullptr;
                    delete root;
                    root = s1.child;

                    r    = root;

                    return (nullptr);
                }


                if (s1.child != nullptr)       //Means the previous merge operation has created a new deficiency
                {
                    int e = isRotationPossible(p,r);

                    if (e == 1)
                        s1 =  rotateRight(p,r,s1.midValue,s1.child);        //MidValue is just a dummy here. Used to complete the argument list

                    else if (e == 2)
                        s1 =  rotateLeft(p,r,s1.midValue,s1.child);

                    else
                        s1 = merge(p,r,s1.child);                 //Merging is to be done if the rotation didn't work

                    return s1;
                }


                //Swap with predecessor and delete the non leaf node

                two3node* current;
                Point temp;

                if ( (r -> n == 2) && (r -> k2 == d) )    //If r is a 3 node and key to be deleted is k2
                {
                    temp    = r -> k2;
                    current = r -> middle;

                    p = r;

                    while (current -> left != nullptr)     //Because predecessor is always in a leaf node
                    {
                        p = current;

                        if (current -> n == 1)
                        {
                            current = current -> middle;    //If current is a 2 node then move towards its middle
                        }

                        else
                        {
                            current = current -> right;     //If current is a 3 node then move towards its right
                        }
                    }


                    if (current -> n == 1)              //If predecessor is in a 2 node
                    {
                        r -> k2       = current -> k1;
                        current -> k1 = temp;
                    }

                    else                                //If predecesoor is in a 3 node
                    {
                        r -> k2       = current -> k2;
                        current -> k2 = temp;
                    }
                }


                else                        //If the key to be deleted is k1 then the processing is the same irrespective
                    //of the fact whether r is a 2 node or a 3 node
                {
                    temp    = r -> k1;
                    current = r -> left;

                    p = r;

                    while (current -> left != nullptr)     //Because predecessor is always in a leaf node
                    {
                        p = current;

                        if (current -> n == 1)          //If current is a 2 node then move towards its middle
                        {
                            current = current -> middle;
                        }

                        else                            //If current is a 3 node then move towards its right
                        {
                            current = current -> right;
                        }
                    }


                    if (current -> n == 1)  //Predecessor is in a 2 node
                    {
                        r -> k1       = current -> k1;
                        current -> k1 = temp;
                    }

                    else if (current -> n == 2) //Predecessor is in a 3 node
                    {
                        r -> k1       = current -> k2;
                        current -> k2 = temp;
                    }
                }

                current -> n--;             //Deleting that key value
                r = current;
            }


                //CASE 2 When key from leaf node is to be deleted

            else if ((r -> left == nullptr) && ( (r -> k1 == d) || (r -> k2 == d) ))     //r is a Leaf node, Simply delete
            {
                if (r -> n == 2)           //r is a 3 node
                {
                    if (r -> k1 == d)       //k1 is to be deleted
                    {
                        r -> k1 = r -> k2;  //Shift K2 to K1's place
                    }
                }

                r -> n --;          //Deleting that key value
            }


            //After deletion, checking for underflow

            //Check for underflow
            //If rotation possible then do rotation
            //else do merge

            if ( (r -> n == 0) && (p == r) )         //Means if root was deleted
            {
                delete r;
                root = nullptr;
            }

            else if (r -> n == 0)
            {

                usefulData s1;

                int e = isRotationPossible(p,r);


                if (e == 1)
                    s1 =  rotateRight(p,r,s1.midValue,nullptr);            //MidValue is just a dummy here. Used to complete the parameter list

                else if (e == 2)
                    s1 =  rotateLeft(p,r,s1.midValue,nullptr);

                else
                    s1 = merge(p,r,nullptr);                 //Merging is to be done if the rotation didn't work

                return s1;
            }

        }

        return (nullptr);
    }


    void searchFor(Point item){
        search(root, item);
    }


    void search (two3node* r, Point d){
        if (r != nullptr){
            if (r -> n == 1)            //Two Node
            {
                if (d == r -> k1) {
                    search ( r -> left , d);
                    std::cout << r->k1 << std::endl;
                    search( r -> right, d);
                }

                else if (d < r -> k1){
                    search (r -> left , d);
                }

                else{
                    search (r -> middle, d);
                }
            }

            else                        //Three Node
            {
                if (d == r -> k1) {
                    search(r->left, d);
                    std::cout << r->k1 << std::endl;
                    search(r->middle, d);
                    if (d == r->k2){
                        std::cout << r -> k2;
                        search(r->right, d);
                    }
                } else if (d == r -> k2) {
                    search(r->middle, d);
                    std::cout << r->k2 << std::endl;
                    search(r->right, d);
                } else if (d < r -> k1){
                    search (r -> left , d);
                } else if (d < r-> k2){
                    search (r -> middle, d);
                } else search (r -> right, d);
            }
        }
    }


    void searchForRange(Point left, Point right){
        search(root, left, right);
    }


    void search(two3node* r, Point left, Point right){
        if (r != nullptr){
            if (r -> n == 1)            //Two Node
            {
                if (left <= r -> k1 && right >= r -> k1) {
                    search ( r -> left , left, right);
                    std::cout << r->k1 << std::endl;
                    search( r -> middle, left, right);
                } else if (right < r -> k1){
                    search (r -> left , left, right);
                } else{
                    search (r -> middle, left, right);
                }
            }

            else                        //Three Node
            {
                if (r -> k1 <= right && r -> k1 >= left){
                    std::cout << r -> k1 << std::endl;
                    search(r->left, left, right);
                    search(r->middle, left, right);
                    if (r -> k2 <= right){
                        std::cout << r -> k2 << std::endl;
                        search(r->right, left, right);
                    }
                } else if (r->k2 <= right && r->k2 >= left){
                    std::cout << r->k2 << std::endl;
                    search(r->middle, left, right);
                    search(r->right, left, right);
                } else if (r -> k1 < left && r -> k2 > right){
                    search(r->middle, left, right);
                } else if (r->k1 > right){
                    search(r->left, left, right);
                } else if (r->k2 < left){
                    search(r->right, left, right);
                }
            }
        }
    }



    void printTree(){
        print(root, {});
    }


    void print (two3node* r, std::vector<int> path){
        if(r != nullptr){
            if (r -> n == 1){
                path.push_back(0);
                print (r -> left, path);
                path.pop_back();
                std::cout << "{ ";
                for (auto i : path){
                    std::cout << i << " ";
                }
                std::cout << "} -- " << r -> k1 << std::endl;
                path.push_back(1);
                print (r -> middle, path);
            }
            else{
                path.push_back(0);
                print (r -> left, path);
                path.pop_back();


                std::cout << "{ ";
                for (auto i : path){
                    std::cout << i << " ";
                }
                std::cout << "} -- " << r -> k1 << std::endl;


                path.push_back(1);
                print (r -> middle, path);
                path.pop_back();


                std::cout << "{ ";
                for (auto i : path){
                    std::cout << i << " ";
                }
                std::cout << "} -- " << r -> k2 << std::endl;


                path.push_back(2);
                print (r -> right, path);
            }
        }
    }

    void add_random(int n){
        for (int i = 0; i < n; ++i){
            add(Point(0, 1000));
        }
    }


    void access(Lambda lambda){
        access(root, lambda);
    }

    void access(two3node* node, Lambda lambda){
        if (node == nullptr) return;
        if (node -> n == 1){
            access(node->left, lambda);
            lambda(node->k1);
            access(node->middle, lambda);
        } else {
            access(node->left, lambda);
            lambda(node->k1);
            access(node->middle, lambda);
            lambda(node->k2);
            access(node->right, lambda);
        }
    }

    void renovate(){
        root->n = 1;
        destroy(root);
        root = nullptr;
    }
};
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"


UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b) {
    auto compare= [&](UnlimitedInt* num1, UnlimitedInt* num2){
        if (num1->get_size() < num2->get_size()) {
            return -1;
        }
        if (num1->get_size() > num2->get_size()) {
            return 1;
        }

        for (int i = num1->get_size() - 1; i >= 0; i--) {
            if (num1->get_array()[i] < num2->get_array()[i]) {
                return -1;
            }
            if (num1->get_array()[i] > num2->get_array()[i]) {
                return 1;
            }
        }
        return 0; // The two numbers are equal
    };
    if (a->to_string() == "0") {
        return new UnlimitedInt(*b);
    }
    if (b->to_string() == "0") {
        return new UnlimitedInt(*a);
    }

    int resultSign =0;
    if(a->get_sign()==1 &&b->get_sign()==1 ){
        resultSign=1;
    }
    else if(a->get_sign()==-1 &&b->get_sign()==-1 ){
        resultSign=-1;
    }
    else{resultSign=1;}

    UnlimitedInt* num1 = new UnlimitedInt(a->get_array(), a->get_capacity(), 1, a->get_size());
    UnlimitedInt* num2 = new UnlimitedInt(b->get_array(), b->get_capacity(), 1, b->get_size());
    while (num2->get_size() > 0) {
       UnlimitedInt* remainder = UnlimitedInt::mod(num1, num2);
        if(num2->to_string()=="1"){break;}
        if (remainder->to_string() == "0") {
            delete remainder;
            break;
        }
        if(compare(num1,num2)==0){
            delete remainder;
            break;
        }
       delete num1 ;
        UnlimitedInt * num1  = new UnlimitedInt(num2->get_array(), num2->get_capacity(), 1, num2->get_size());
        delete num2 ;
        UnlimitedInt * num2  = new UnlimitedInt(remainder->get_array(), remainder->get_capacity(), 1, remainder->get_size());
        delete remainder;
    }
    UnlimitedInt* finalResult = new UnlimitedInt(num2->get_array(), num2->get_capacity(), resultSign, num2->get_size());
    return finalResult;
}


UnlimitedInt* lcm(UnlimitedInt* a, UnlimitedInt* b) {

int resultsign = (a->get_sign())*(b->get_sign());

    UnlimitedInt* absA = new UnlimitedInt(a->get_array(), a->get_capacity(), 1, a->get_size());
    UnlimitedInt* absB = new UnlimitedInt(b->get_array(), b->get_capacity(), 1, b->get_size());

    UnlimitedInt* product = UnlimitedInt::mul(absA , absB);
    UnlimitedInt* gcdResult = gcd(absA, absB);

    UnlimitedInt* lcmResult = UnlimitedInt::div(product, gcdResult);
    UnlimitedInt* lcmResultf =new  UnlimitedInt(lcmResult->get_array(),lcmResult->get_capacity(),resultsign,lcmResult->get_size());
    delete absA;
    delete absB;
    delete product;
    delete gcdResult;
    delete lcmResult;

    return lcmResultf;
}


UnlimitedRational::UnlimitedRational() : p(new UnlimitedInt()), q(new UnlimitedInt()){}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
        p = num;
        q = den;
    }

UnlimitedRational::~UnlimitedRational() {
        // delete p ;
        // delete q ;
    }

UnlimitedInt* UnlimitedRational::get_p() {
        return p;
    }

UnlimitedInt* UnlimitedRational::get_q() {
        return q;
    }

string UnlimitedRational::get_p_str() {
        return p->to_string();
    }

string UnlimitedRational::get_q_str() {
        return q->to_string();
    }

string UnlimitedRational::get_frac_str() {
        // Handle positive/negative cases here
        if (p->get_sign()==-1 && q->get_sign()==-1) {
            return  p->to_string() + "/" + q->to_string();
        } else if (p->get_sign()==-1 && q->get_sign()==1 ) {
            return   p->to_string() + "/" + q->to_string();
        } 
        else if (p->get_sign()==1 && q->get_sign()==-1 ) {
            return   p->to_string() + "/" + q->to_string();
        } 
        else {
            return p->to_string() + "/" + q->to_string();
        }
    }  

 static UnlimitedRational* add(UnlimitedRational* i1, UnlimitedRational* i2){

    UnlimitedInt *q (lcm(i1->get_q() , i2->get_q()));
    UnlimitedInt * nume (UnlimitedInt::add((UnlimitedInt::mul(i1->get_p(),UnlimitedInt::div(q,i1->get_q()))), (UnlimitedInt::mul(i2->get_p(),UnlimitedInt::div(q,i2->get_q())))));
    UnlimitedInt *to_divide(gcd(nume,q));
    nume=UnlimitedInt::div(nume,to_divide);
    q=UnlimitedInt::div(q,to_divide);
    UnlimitedRational* fraction = new UnlimitedRational(nume, q);
        
    return fraction ;
}

    static UnlimitedRational* sub(UnlimitedRational* i1, UnlimitedRational* i2){

    UnlimitedInt *q (lcm(i1->get_q() , i2->get_q()));
    UnlimitedInt * nume (UnlimitedInt::sub((UnlimitedInt::mul(i1->get_p(),UnlimitedInt::div(q,i1->get_q()))), (UnlimitedInt::mul(i2->get_p(),UnlimitedInt::div(q,i2->get_q())))));
    UnlimitedInt *to_divide(gcd(nume,q));
    nume=UnlimitedInt::div(nume,to_divide);
    q=UnlimitedInt::div(q,to_divide);
    UnlimitedRational* fraction = new UnlimitedRational(nume, q);

    return fraction ;
    }

    static UnlimitedRational* div(UnlimitedRational* i1, UnlimitedRational* i2){
        UnlimitedInt *p (UnlimitedInt::mul(i1->get_p() , i2->get_q()));
        UnlimitedInt *q (UnlimitedInt::mul(i1->get_q() , i2->get_p()));
        UnlimitedInt *to_divide(gcd(p,q));
        q=UnlimitedInt::div(q,to_divide);
        p=UnlimitedInt::div(p,to_divide);
        UnlimitedRational* fraction = new UnlimitedRational(p, q);

        return fraction ;
    }

    static UnlimitedRational* mul(UnlimitedRational* i1, UnlimitedRational* i2){

        UnlimitedInt *p (UnlimitedInt::mul(i1->get_p() , i2->get_p()));
        UnlimitedInt *q (UnlimitedInt::mul(i1->get_q() , i2->get_q()));
        UnlimitedInt *to_divide(gcd(p,q));
        q=UnlimitedInt::div(q,to_divide);
        p=UnlimitedInt::div(p,to_divide);
        UnlimitedRational* fraction = new UnlimitedRational(p, q);

        return fraction ;

    }




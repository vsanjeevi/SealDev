#include "examples.h"
#include "../src/seal/seal.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <istream>
#include <streambuf>



using namespace std;
using namespace seal;

int main(int argc, char *argv[] )
{

cout << "SEAL KEYGEN : Generating keys " << endl; 
cout << " " << endl; 


//Generating context
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(1024);
    SEALContext context(parms);

//Generating Public and Private Keys
    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

//Preparation of Keys for writing to file 

//save public key to stringstream pk
     std::stringstream pk;
     public_key.save(pk);
//save stringstream to string printpk 
     std::string printpk = pk.str();

//save secret key to stringstream sk
      std::stringstream sk;
      secret_key.save(sk);
//save stringstream to string printpk 
     std::string printsk = sk.str();


//writing contents of Public key to pk file in /tmp folder
   std::ofstream out("/tmp/pk");
   out << printpk;
   out.close();


//writing contents of Secret key to sk file in /tmp folder
   std::ofstream out1("/tmp/sk");
   out1 << printsk;
   out1.close();


    return 0;
}

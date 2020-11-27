#include "examples.h"
#include "../src/seal/seal.h"
#include <sstream>
#include <string>
#include <iostream>
#include <istream>
#include <streambuf>
#include <sstream>
#include <fstream>


using namespace std;
using namespace seal;

int main(int argc, char *argv[] )
{

cout << " SEAL ENCRYPTION " << endl; 


//Generating context
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(1024);
    SEALContext context(parms);

//file operations
//open file with ifstream variable cipherstring
//load file contents from pk.txt file to ostringstream variable
//loading ostringstream contents to string variable
ifstream cipherstring("/tmp/pk");

std::string temp;

if(cipherstring) {
   ostringstream streamt;
   streamt << cipherstring.rdbuf();
   temp = streamt.str();
}


//Key Operations
//converting the received input public key in string format to stringstream format
      std::istringstream streamsk(temp);

//create a public key variable and load with stringstream values
      PublicKey public_key;
      public_key.load(context, streamsk);

//Load encryptor with public_key
    Encryptor encryptor(context, public_key);


//Getting input from command line
std::string x(argv[1]);
//cout << "value of x " << x << endl;


//print the received data input value
   cout<<"the value of input x " << x << endl;

    Plaintext x_plain(x);
    Ciphertext x_encrypted;

//encrypting using the public_key
    encryptor.encrypt(x_plain, x_encrypted);

//Writing encrypted data to file

//1.convert ciphertext to stringstream
//2.load ciphertext contents in stringstream to string
//3.return string

//ciphertext in binary format is saved to stream ss
       std::stringstream ss;
       x_encrypted.save(ss);
//stream ss is loaded to string
       std::string encrypted_data = ss.str();



//writing contents of encrypted data value to temp file in /tmp folder
   std::ofstream out("/tmp/en");
   out << encrypted_data;
   out.close();

//deleting the tmp files
//std::system("rm /tmp/en*");

    return 0;
}

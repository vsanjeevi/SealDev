#include "examples.h"
#include "../src/seal/seal.h"
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

cout <<" SEAL DECRYPTION " << endl;


//file operations
//READ and LOAD SQUARED CIPHER TEXT VALUE FROM FILE
//open file with ifstream variable cipherstring
//load file contents from ensq.txt file to ostringstream variable
//loading ostringstream contents to string variable
ifstream cipherstring("/tmp/ensq");

std::string temp;

if(cipherstring) {
   ostringstream streamt;
   streamt << cipherstring.rdbuf();
   temp = streamt.str();
}


//Generating context
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));
    parms.set_plain_modulus(1024);
    SEALContext context(parms);



//file operations
//READ and LOAD SECRET KEY VALUE FROM FILE
//open file with ifstream variable cipherstring
//load file contents from sk.txt file to ostringstream variable
//loading ostringstream contents to string variable
ifstream cipherstrings("/tmp/sk");

std::string temps;

if(cipherstrings) {
   ostringstream streamt;
   streamt << cipherstrings.rdbuf();
   temps = streamt.str();
}

//Key Operations
//converting the secret key read from file in string format to stringstream format
      std::istringstream streamsk(temps);

//create a secret key variable and load with stringstream values
      SecretKey secret_key;
      secret_key.load(context, streamsk);
      Decryptor decryptor(context, secret_key);


//Preparation of string return value
//1.convert ciphertext to stringstream
//2.load ciphertext contents in stringstream to string
//3.return string

//ciphertext in binary format is saved to stream stream2
    std:stringstream stream2;
//string temp has square ciphertext contents from ensq.txt file
      stream2.str(temp);



//testing if  stringstream if properly loaded by decryption
//decrypted value in hexadecimal should be equal to square of initial value square

    Ciphertext yxx_encrypted;
    yxx_encrypted.load(context, stream2);
    Plaintext test2;
    decryptor.decrypt(yxx_encrypted, test2);
    cout << "decryption of received ciphertext 0X" << test2.to_string()  << endl;
    std::string message = test2.to_string();

//cout << "****************END OF SEAL_CLIENT2***************** " << endl << endl << endl;

//deleting the tmp files
std::system("rm /tmp/en*");
std::system("rm /tmp/pk");
std::system("rm /tmp/sk");

return 0;

}

# Generate RSA public/private key pair for the CA (Certificate Authority)
#req -- make a new certificate
#-x509 -- in x509 format (the standard format)
#-newkey -- generate a new RSA keypair for this certificate
#rsa:4096 -- make it a 4096 bit RSA key
#-keyout -- filename for the private key
#-out -- filename for the certificate
#-days 30 -- this certificate expires 30 days from now
#-nodes -- don't encrypt the certificate/private key
openssl req -x509 -newkey rsa:4096 -keyout CAprivateKey.pem -out CAcertificate.pem -days 30 -nodes


# Generate server keys + certificate signature requests (.csr)
openssl req -new -newkey rsa:4096 -nodes -keyout serverPrivate.key -out server.csr

# Generate server keys + certificate signature requests (.csr)
openssl req -new -newkey rsa:4096 -nodes -keyout clientPrivate.key -out client.csr

# Setup CA for signing
mkdir certs newcerts keys outputs
touch index.txt
echo 1000 > serial

# Server
openssl ca -config config.cnf -cert CAcertificate.pem -keyfile CAprivateKey.pem -in server.csr -out CASignedServerCertificate.pem
openssl pkcs8 -topk8 -outform DER -in serverPrivate.key -out serverPrivateKey.der -nocrypt # Convert to .der

# Client
openssl ca -config config.cnf -cert CAcertificate.pem -keyfile CAprivateKey.pem -in client.csr -out CASignedClientCertificate.pem
openssl pkcs8 -topk8 -outform DER -in clientPrivate.key -out clientPrivateKey.der -nocrypt # Convert to .der

# Verify - Hashes should match
openssl rsa -in clientPrivate.key -noout -modulus | openssl sha256
openssl x509 -noout -modulus -in CASignedClientCertificate.pem | openssl sha256
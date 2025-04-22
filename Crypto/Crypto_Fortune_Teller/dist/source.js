const crypto = require('crypto');

const FLAG = "CSL{REDACTED}"

// Generate 7 random numbers
let numbers = Array.from({ length: 7 }, () => Math.random());

// Output the first 6 numbers
console.log("Random Numbers:", numbers.slice(0, 6));

// Convert the 7th number into a 256-bit key
const key = crypto.createHash('sha256').update(numbers[6].toString()).digest();

// AES Encrypt flag using key
function encryptAES(text, key) {
    const cipher = crypto.createCipheriv('aes-256-ecb', key, null);
    let encrypted = cipher.update(text, 'utf8', 'hex');
    encrypted += cipher.final('hex');
    return encrypted;
}

const encryptedFlag = encryptAES(FLAG, key);
console.log("Encrypted Flag:", encryptedFlag);
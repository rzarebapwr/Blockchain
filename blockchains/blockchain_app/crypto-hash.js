const crypto = require('crypto');


const cryptoHash = (...inputs) => {

    // Hashing object
    const hash = crypto.createHash('sha256');

    // Fit on sorted list of received strings
    hash.update(inputs.sort().join(' '));

    return hash.digest('hex');
    
}

module.exports = cryptoHash;
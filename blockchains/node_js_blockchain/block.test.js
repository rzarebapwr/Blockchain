const Block = require('./block');
const { GENESIS_BLOCK_DATA } = require('./config.js');
const cryptoHash = require('./crypto-hash');


describe('Block', () => {
    const timestamp = 'a-date';
    const lastHash = 'some-hash';
    const hash = 'some-hash';
    const data = 'some-data';

    block = new Block({ timestamp, lastHash, hash, data });

    it('constructor definied properly', () => {
        expect(block.timestamp).toEqual(timestamp);
        expect(block.lastHash).toEqual(lastHash);
        expect(block.hash).toEqual(hash);
        expect(block.data).toEqual(data);
    });
    
    describe('getGenesisBlock()', () => {
        const genesisBlock = Block.getGenesisBlock();

        it('Genesis block is instance of Block class', () => {
            expect(genesisBlock instanceof Block).toBe(true);
        });

        it('Genesis block is equal to GENESIS_BLOCK_DATA', () => {
            expect(genesisBlock).toEqual(GENESIS_BLOCK_DATA);
        });
    });

    describe('mineBlock()', () => {
        const lastBlock = Block.getGenesisBlock();
        const data = 'some-data';
        const minedBlock = Block.mineBlock({ lastBlock, data });

        it('returns Block instance', () => {
            expect(minedBlock instanceof Block).toBe(true);
        });

        it('last hash of the mined block is equal to hash of the previous block', () => {
            expect(minedBlock.lastHash).toEqual(lastBlock.hash);
        });

        it('has data field', () => {
            expect(minedBlock.data).toEqual(data);
        });

        it('has timestamp field', () => {
            expect(minedBlock.timestamp).not.toEqual(undefined);
        });

        it('hashes proper inputs', () => {
            expect(minedBlock.hash)
            .toEqual(cryptoHash(minedBlock.timestamp, minedBlock.lastHash, minedBlock.data));

        });



    });

});
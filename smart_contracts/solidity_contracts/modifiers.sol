pragma solidity >=0.4.22 <0.7.0;

/**
 */

 interface Bank {
     function getBalance() external view returns (uint);
     function deposit(uint amount) external;
     function withdraw(uint amount) external;
 }


 contract MyContract is Bank {
     uint private value;
     address private owner;

     constructor(uint _value) public {
         value = _value;
         owner = msg.sender;
     }

     modifier onlyOwner {
         require(msg.sender == owner);
         _;
     }

     function getBalance() public override view returns(uint) {
         return value;
     }

     function deposit(uint amount) public override onlyOwner {
         value += amount;
     }

     function withdraw(uint amount) public override onlyOwner {
         value -= amount;
     }

 }

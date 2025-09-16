import React from "react";
  
  
 
  
  const Deposit =({handleDeposit,setDepositAmount,depositAmount,setSubPanel}) => {
  return ( <div className="deposit-panel">
                      <h2>New Deposit</h2>
                      <form onSubmit={handleDeposit}>
                        <input type="number" value={depositAmount} required onChange={(e) => setDepositAmount(e.target.value)} />
                        <button type="submit">Submit</button>
                         <button className="btn" onClick={() => setSubPanel("")}>Close</button>
                      </form>
                    </div>
   );
};
const Withdraw =({handleWithdraw,withdrawAmount,setWithdrawAmount,setSubPanel}) => {
return  (<div className="withdraw-panel">
                      <h2>New Withdraw</h2>
                      <form onSubmit={handleWithdraw}>
                        <input type="number" value={withdrawAmount} onChange={(e) => setWithdrawAmount(e.target.value)} />
                        <button type="submit">Submit</button>
                         <button className="btn" onClick={() => setSubPanel("")}>Close</button>
                      </form>
                    </div>
);};
export { Deposit,Withdraw };
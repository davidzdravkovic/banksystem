 import React from "react";
 
 
 
 const CreateTransaction = ({toAccount,setToAccount,transactionSum,setTransactionSum,typeTransaction,setTypeTransaction,setSubPanel,handleTransaction}) => {
 return (<div className="transaction-panel">
                      <h2>New Transaction</h2>
                      <form onSubmit={handleTransaction}>
                        <>Enter account number</>
                        <input type="number" value={toAccount} required onChange={(e) => setToAccount(e.target.value)}/>
                        <>Enter transaction sum</>
                        <input type="number" value={transactionSum} required onChange={(e) => setTransactionSum(e.target.value)} />
                        <select   value={typeTransaction || ""}  required onChange={(e) => setTypeTransaction(e.target.value)}>
                          <option value="" disabled>Select type</option>
                          <option value="Sending">Sending</option>
                          <option value="Asking">Asking</option>ansactionID
                        </select>
                        <button type="submit">Submit</button>
                        <button type="button" onClick={() => { setToAccount(""); setTransactionSum(""); setTypeTransaction("");setSubPanel(""); }}>Cancel</button>
                      </form>

                    </div> );};

const Transaction =({setTransactionsView,handleInboxGet,handleSentGet,inboxTransactions,sentTransactions,
handleAccept,handleDecline,setSubPanel,transactionType,transactionsView}) => 
{
   return  ( <div className="transactions-panel">
                      <h2>Transactions</h2>
                      <select value={transactionsView}   onChange={(e) => {setTransactionsView(e.target.value);
                      if (e.target.value === "inbox") handleInboxGet(); else if (e.target.value === "sent") handleSentGet();}}>
                      <option value="inbox">Inbox</option>
                      <option value="sent">Sent</option>
                      </select>

                     {transactionsView === "inbox" && ( 
                      inboxTransactions.length > 0 ? (
                     <table>
                    <thead>
                    <tr>
                      <th>Sender Number</th>
                      <th>Amount</th>
                      <th>Transaction ID</th>
                      <th>Type</th>
                      <th>Action</th>
                        </tr>
                      </thead>
                         <tbody>
                       {inboxTransactions.map((trans) => (
                      <tr key={trans.transactionID}>
                       <td>{trans.senderNumber}</td>
                    <td>{trans.amount}</td>
                     <td>{trans.transactionID}</td>
                    <td>{transactionType(trans.type)}</td>
                     <td>
                      <button onClick={() =>  {if (window.confirm("Are you sure you want to accept this transaction?")) {handleAccept(trans.transactionID);}}}>✅</button>
                        <button onClick={() =>  {if (window.confirm("Are you sure you want to accept this transaction?")) {handleDecline(trans.transactionID);}}}>❌</button>
                       </td>
                       </tr>
                             ))}
                                </tbody>
                              </table>
                             ): 
                           (<p>Empty inbox</p>)
                               )}

                      {transactionsView === "sent" &&(
                      sentTransactions.length > 0 ? (
                        <table>
                        <thead>
                          <tr>
                          <th>Receiver Number</th>
                            <th>Amount</th>
                           <th>Transaction Number</th>
                           <th>Type</th>
                           <th>Action</th>
                           </tr>
                            </thead> 
                            <tbody>
                             {sentTransactions.map((trans) => (
                           <tr key={trans.transactionID}>
                              <td>{trans.receiverNumber}</td>
                                  <td>{trans.amount}</td>
                                <td>{trans.transactionID}</td>
                            <td>{transactionType(trans.type)}</td>
                              <td>
                             <button onClick={() =>  {if (window.confirm("Are you sure you want to decline this transaction?")) {handleDecline(trans.transactionID);}}}>❌</button>
                                 </td>     
                                    </tr>
                                               ))}
                                   </tbody>
                               </table>
                          ): (<p>No sent transactions</p>)
                                ) }
                      <button className="btn" onClick={() => setSubPanel("")}>Close</button>
                      </div>
   ); };



   const TransactionHistory = ({transactionHistory,handleDelete,transactionType}) => {
 return (                     
 
 
 
 
                              <table>
                              <thead>
                                <tr>
                            <th>Receiver Name</th>
                            <th>Sender Name</th>
                            <th>Amount</th>
                            <th>Transaction ID</th>
                            <th>Type</th>
                            <th>Status</th>
                            <th>Action</th>
                                </tr>
                             </thead>
                            <tbody>
                             {transactionHistory.map((trans) => (
                               <tr key={trans.transactionID}>
                                <td>{trans.receiverNumber}</td>
                               <td>{trans.senderNumber}</td>
                              <td>{trans.amount}</td>
                               <td>{trans.transactionID}</td>
                              <td>{transactionType(trans.type)}</td>
                              <td>{trans.transactionStatus} </td>
                              <td>
                               <button
                             className="btn btn-decline"
                            onClick={() => {if (window.confirm("Are you sure you want to delete this transaction?")) 
                             {handleDelete(trans.transactionID);}}}>❌</button>
                               </td>
                               </tr>
                                ))}
                             </tbody>
                            </table>
   );};


export {CreateTransaction,Transaction,TransactionHistory};
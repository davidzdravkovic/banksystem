 import React from "react";
 
 
 
 const CreateTransaction = ({
  toAccount,
  setToAccount,
  transactionSum,
  setTransactionSum,
  typeTransaction,
  setTypeTransaction,
  setSubPanel,
  handleTransaction,
  pending,
  setPending
}) => {


  const confirmTransaction = (e) => {
    e.preventDefault();
    setPending(true); // show confirmation modal
  };

  const handleConfirm = () => {
    handleTransaction({ preventDefault: () => {} }); // call the dashboard handler
    setPending(false);
  };

  return (
    <div className="transaction-panel">
      <h2>New Transaction</h2>
      <form onSubmit={confirmTransaction}>
        <label>Enter account number</label>
        <input
          type="number"
          value={toAccount || ""}
          required
          onChange={(e) => setToAccount(e.target.value)}
        />

        <label>Enter transaction sum</label>
        <input
          type="number"
          value={transactionSum || ""}
          required
          onChange={(e) => setTransactionSum(e.target.value)}
        />

        <label>Select transaction type</label>
        <select
          value={typeTransaction || ""}
          required
          onChange={(e) => setTypeTransaction(e.target.value)}
        >
          <option value="" disabled>Select type</option>
          <option value="Sending">Sending</option>
          <option value="Asking">Asking</option>
        </select>

        <div className="transaction-buttons">
          <button type="submit">Submit</button>
          <button
            type="button"
            onClick={() => {
              setToAccount("");
              setTransactionSum("");
              setTypeTransaction("");
              setSubPanel(null);
            }}
          >
            Cancel
          </button>
        </div>
      </form>

      {pending && (
        <div className="modal-overlay">
          <div className="modal">
            <p>Are you sure you want to create this transaction?</p>
            <button className="btn" onClick={handleConfirm}>Yes</button>
            <button className="btn" onClick={() => setPending(false)}>Cancel</button>
          </div>
        </div>
      )}
    </div>
  );
};

const Transaction = ({
  setTransactionsView,
  handleInboxGet,
  handleSentGet,
  inboxTransactions,
  sentTransactions,
  handleAccept,
  handleDecline,
  setSubPanel,
  transactionType,
  transactionsView,
  loadingSent,
  transactionToConfirm,
  transactionToDelete,
  setTransactionToConfirm,
  setTransactionToDelete,
  actionType,
  setActionType 
}) => {


  const confirmAction = () => {
    if (actionType === "accept") handleAccept(transactionToConfirm);
    else if (actionType === "decline") handleDecline(transactionToConfirm);
    setTransactionToConfirm(null);
    setActionType(null);
  };

  return (
    <div className="transactions-panel">
      <h2>Transactions</h2>
      <select
        value={transactionsView}
        onChange={(e) => {
          setTransactionsView(e.target.value);
          if (e.target.value === "inbox") handleInboxGet();
          else if (e.target.value === "sent") handleSentGet();
        }}
      >
        <option value="inbox">Inbox</option>
        <option value="sent">Sent</option>
      </select>

      {/* Inbox */}
      {transactionsView === "inbox" &&
        (inboxTransactions.length > 0 ? (
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
                    <button
                      onClick={() => {
                        setTransactionToConfirm(trans.transactionID);
                        setActionType("accept");
                      }}
                    >
                      ✅
                    </button>
                    <button
                      onClick={() => {
                        setTransactionToConfirm(trans.transactionID);
                        setActionType("decline");
                      }}
                    >
                      ❌
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        ) : (
          <p className="empty-message">📭 Your inbox is empty</p>
        ))}

      {/* Sent */}
      {loadingSent ? (
        <p>Loading sent transactions...</p>
      ) : (
        transactionsView === "sent" &&
        (sentTransactions.length > 0 ? (
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
                    <button
                      onClick={() => {
                        setTransactionToConfirm(trans.transactionID);
                        setActionType("decline");
                      }}
                    >
                      ❌
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        ) : (
          <p className="empty-message">📤 No sent transactions</p>
        ))
      )}

      <button className="btn" onClick={() => setSubPanel(null)}>
        Close
      </button>

      {/* Confirmation modal */}
      {transactionToConfirm && (
        <div className="modal-overlay">
          <div className="modal">
            <p>
              Are you sure you want to {actionType === "accept" ? "accept" : "decline"} this transaction?
            </p>
            <button className="btn" onClick={confirmAction}>
              Yes
            </button>
            <button className="btn" onClick={() => setTransactionToConfirm(null)}>
              Cancel
            </button>
          </div>
        </div>
      )}
    </div>
  );
};




   const TransactionHistory = ({transactionHistory,handleDelete,transactionType,setSubPanel,setTransactionToDelete,transactionToDelete}) => {
 return (                     
 
 
             <div>
      <h1 className="header-normal">Transaction history</h1>

      {transactionHistory.length === 0 ? (
        <p className="empty-message">📤 No transaction history</p>
      ) : (
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
                <td>{trans.transactionStatus}</td>
                <td>
                  <button className="btn btn-decline" onClick={() => setTransactionToDelete(trans.transactionID)}>❌</button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      )}

      <button className="btn" onClick={() => setSubPanel(null)}>Back</button>

      {/* Custom delete confirmation modal */}
      {transactionToDelete && (
        <div className="modal-overlay">
          <div className="modal">
            <p>Are you sure you want to delete this transaction?</p>
            <button
              className="btn"
              onClick={() => {
                handleDelete(transactionToDelete);
                setTransactionToDelete(null);
              }}
            >
              Yes
            </button>
            <button className="btn" onClick={() => setTransactionToDelete(null)}>Cancel</button>
          </div>
        </div>
      )}
    </div>
                            
   );};


export {CreateTransaction,Transaction,TransactionHistory};
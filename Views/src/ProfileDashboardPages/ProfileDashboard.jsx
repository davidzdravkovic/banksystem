import React, { useEffect,useState} from "react";
import { useNavigate} from "react-router-dom";
import profilImage from "../images/profile.jpg";
import bankLogo from "../images/bank_logo.png"
import { Deposit,Withdraw } from "./WithDepo";     
import { CreateTransaction,Transaction,TransactionHistory } from "./Transaction";
import { CreateAccount,SearchAccount } from "./Accounts";
import Notification from "./Notification";


export default function ProfileDashboard() {
 const userType = localStorage.getItem("userType") || "unknown";
 const userId = localStorage.getItem("userId") || "unknown";
 const userName = localStorage.getItem("userName") || "uknowns";
 
const [accounts, setAccounts] = useState([]);
const [activeSubPanel,setSubPanel]=useState(null);
const [depositAmount, setDepositAmount] = useState(0);
const [withdrawAmount, setWithdrawAmount] = useState(0);

const[selectedType, setType] =useState("");
const[enteredAccountNumber, setEnterID] = useState("");
const[balance,setBalance]=useState(1);

const[toAccount,setToAccount] =useState(null);
const[transactionSum,setTransactionSum] =useState(null);
const[typeTransaction,setTypeTransaction] =useState(null);


const [transactionsView, setTransactionsView] = useState();
const [inboxTransactions, setInboxTransactions] = useState([]);
const [sentTransactions, setSentTransactions] = useState([]);
const [transactionHistory, setTransactionHistory] =useState([]);

const [loadingInbox, setLoadingInbox] = useState(false);
const [loadingSent, setLoadingSent] = useState(false);
const [transactionToDelete, setTransactionToDelete] = useState(null);

  const [transactionToConfirm, setTransactionToConfirm] = useState(null);
  const [actionType, setActionType] = useState(null); // "accept" or "decline"
  const [pending, setPending] = useState(false);




const handleOpenProfile = (acc) => {
  setSelectedAccount(acc)
  setPanel("yes");
  setEnterID(acc.accountNumber);
  setType(acc.accountType);
  setBalance(acc.balance);
  
}
const setTransactions = (selectedTransaction) => {
 setTransactionSum(selectedTransaction.receiver);
 setTypeTransaction(selectedTransaction.typeTransaction);
}


const [notification, setNotification] = useState(null);

const showNotification = (message, type) => {
  setNotification({ message, type });
  setTimeout(() => setNotification(null), 3000); // hide after 3s
};




const handleHistory = async () => {

  const historyUrl=`http://localhost:8080/transaction?accountNumber=${enteredAccountNumber}&type=history`

  try {
    
  const controller=new AbortController();
  const timeoutId = setTimeout(() => controller.abort(), 5000);

  const respons = await fetch(historyUrl, {
    method: "GET",
    headers: {"Content-Type": "application/json"},
    signal: controller.signal
  }); 

  clearTimeout(timeoutId);

  const data= await respons.json();

  if(data.status === true) {
      setTransactionHistory(data.transactions);
      
} else {
  console.error("Fetch transaction failed");
}
}
catch(err) {
 console.error("Fetch transaction failed", err);
}
}




const handleDelete = async (transactionID) => {

const deleteUrl=`http://localhost:8080/transaction_disable?transactionID=${transactionID}&accountNumber=${enteredAccountNumber}`;

  try {

  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);

  const response = await fetch(deleteUrl, {
    method: "PATCH",
    headers: {"Content-Type": "application/json"},
    signal: controller.signal
  }); 

  clearTimeout(timeoutId);

  const data= await response.json();
 

   
  

  if(data.status === true) {
     handleHistory();

} else {
  console.error("Fetch transaction failed");
}
}
catch(err) {
 console.error("Fetch transaction failed", err);
}

}
const handleSentGet = async () => {

   setLoadingSent(true);

  const sentUrl=`http://localhost:8080/transaction?accountNumber=${enteredAccountNumber}&type=sent`
  try {const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);
  const respons = await fetch(sentUrl, {
    method: "GET",
    headers: {"Content-Type": "application/json"},
    signal: controller.signal
  }); 
  clearTimeout(timeoutId);


  const data= await respons.json();

  setSentTransactions(data);
  setLoadingSent(false);

  if(data.status === true) {
      setSentTransactions(data.transactions);
      setSubPanel("transactions");
      setTransactionsView("sent");

} else {
  console.error("Fetch transaction failed");
}
}
catch(err) {
 console.error("Fetch transaction failed", err);
}
};

const handleInboxGet = async () => {

  const getUrl=`http://localhost:8080/transaction?accountNumber=${enteredAccountNumber}&type=inbox`;
  try {
    const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);

  const respons = await fetch(getUrl, {
    method: "GET",
    headers: {"Content-Type": "application/json"},
    signal: controller.signal
  }); 

  clearTimeout(timeoutId);

  const data= await respons.json();

  if(data.status === true) {
      setInboxTransactions(data.transactions);
      setSubPanel("transactions");
      setTransactionsView("inbox");
} else {
  console.error("Fetch transaction failed");
}
}
catch(err) {
 console.error("Fetch transaction failed", err);
}
};


const handleTransaction = async (e) => {
  setSubPanel(null)
  e.preventDefault();
  try {
    const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);

  const respons = await fetch('http://localhost:8080/transaction_validate', {
    method: "POST",
    headers: {"Content-Type": "application/json"},
    body: JSON.stringify({ senderNumber:enteredAccountNumber, amount: Number(transactionSum),
    transactionType: typeTransaction,
    receiverNumber: toAccount }),
    signal: controller.signal
  }); 

  clearTimeout(timeoutId);
  const data= await respons.json();

 if (respons.ok) {
  showNotification("Transaction created successfully ✅", "success");
} else {
  showNotification("Transaction failed ❌", "error");
}


  if(data.status === true) {
 setPanel("yes");
} else {
  console.error("Transaction failed on server");
}
}
catch(err) {
 console.error("Transaction failed:", err);
}
   
};

function getAccountType (accountType) {
  switch(accountType) {
    case "checking_accounts":
      return "Checking Account";
    case "saving_accounts":
      return "Savings Account";
      case"credit_accounts":
      return "Credit Account";
    default:
      return accountType; 
  }
}
function getCurrentAccountType(selectedType) {
  switch(selectedType) {
    case "checking_accounts":
      return "Checking Account";
    case "saving_accounts":
      return "Savings Account";
    case "credit_accounts":
      return "Credit Account";
    default:
      return selectedType;
  }
}
function transactionType(type) {
  switch(type) {
    case "1":
      return "Sending";
      case "2":
        return "Asking";
        default:
          return selectedType;
  }
}



 const navigate1 = useNavigate();
 const handleAction = () => {
  localStorage.clear(); // clear login info
  navigate1("/");   // redirect to home page
};


const handleEnterID =(e)=> {
  setEnterID(e.target.value)
}
const handleType =(e)=> {
  setType(e.target.value)
}

 const navigate = useNavigate();
 useEffect(() => {
    const userType = localStorage.getItem("userType");
    if (!userType) {
      navigate("/login"); 
    }
  }, [navigate]);

const handleDecline = async (transactionID) => {
 
const  acceptUrl = `http://localhost:8080/transaction_decline?transactionNumber=${transactionID}`;
try {
  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);

  const response = await fetch (acceptUrl, {
  method:"PATCH",
  headers: {"Content-Type": "application/json"},

   signal: controller.signal
  }); 
  clearTimeout(timeoutId);

  if (response.ok) {
     
      if (transactionsView === "sent") {
        handleSentGet();
      }
      else if(transactionsView === "inbox") {
        handleInboxGet();
      }
    }
const data= await response.json();
if(data.status) {

}

}

catch(err) {

}
}

 
const handleAccept = async (transactionID) => {
 
const  acceptUrl = `http://localhost:8080/transaction_accept?transactionNumber=${transactionID}`;
try {
  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);

  const response = await fetch (acceptUrl, {
  method:"PATCH",
  headers: {"Content-Type": "application/json"},

   signal: controller.signal
  }); 
  clearTimeout(timeoutId);

  if (response.ok) {
     
      if (transactionsView === "inbox") {
        handleInboxGet();
      }
    }
const data= await response.json();
if(data.status) {
setBalance(data.balance);
}

}

catch(err) {

}
}

const [selectedAccount, setSelectedAccount] = useState(null);
const [selectedTransaction, setSelectedTransaction] = useState(null);



const handleDeposit = async (e) => {
    e.preventDefault(); // stop form reload
    setSubPanel(null)
   const depositUrl = `http://localhost:8080/deposit?accountNumber=${enteredAccountNumber}`;
try {
  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000); // 5-second timeout
  const respons= await fetch (depositUrl, {
    method: "PATCH",
    headers: {"Content-Type": "application/json"},
    body: JSON.stringify({ amount: Number(depositAmount) }),
    signal: controller.signal
  }); 
  clearTimeout(timeoutId);
  const data= await respons.json();

  if (respons.ok) {
  showNotification("Deposit succeed✅", "success");
} else {
  showNotification("Deposit failed ❌", "error");
}

  if(data.status === true) {
  setBalance(data.balance);
} else {
  console.error("Deposit failed on server");
}
}
catch(err) {
 console.error("Deposit failed:", err);
}
}

const handleWithdraw = async (e) => {

    e.preventDefault(); // stop form reload
    setSubPanel(null)

    const withdrawUrl = `http://localhost:8080/withdraw?accountNumber=${enteredAccountNumber}`;
try {
  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000); // 5-second timeout
  const respons= await fetch (withdrawUrl, {
    method: "PATCH",
    headers: {"Content-Type": "application/json"},
    body: JSON.stringify({ amount: Number(withdrawAmount) }),
    signal: controller.signal
  }); 
  clearTimeout(timeoutId);

  const data= await respons.json();

  if (respons.ok) {
  showNotification("Withdraw succeed✅", "success");
} else {
  showNotification("Withdraw failed ❌", "error");
}


  if(data.status === true) {
  setBalance(data.balance);
} 
else {
  console.error("Withdraw failed on server");
}
}
catch(err) {
 console.error("Withdraw failed:", err);
}
}

   const newAccount = {
   
  "accountNumber": enteredAccountNumber, 
  "personalID":userId,
  "accountType": selectedType,
  "fullName":userName,
   }

  const handleLogin = async (e) => {
    e.preventDefault();
  
try {
  const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000); 
  const respons= await fetch ("http://localhost:8080/create", {
    method: "POST",
    headers: {"Content-Type": "application/json"},
    body: JSON.stringify(newAccount),
    signal: controller.signal
  }); 
  clearTimeout(timeoutId);


const data = await respons.json();
  
  
 
    if (data.success) {
  setSelectedAccount(data.account);
  handleOpenProfile(data.account); 
  setPanel("yes");
}

}

catch (err) {
  console.error("Account creation failed:", err);
}

  }
  const url = `http://localhost:8080/search?personalID=${userId}`;

  const handleSearchAccount = async (e) =>  {
    
    const controller=new AbortController();
   const timeoutId = setTimeout(() => controller.abort(), 5000);
    try{ const response = await fetch (url, {
      method:"GET",
      headers: {"Content-Type": "application/json"},
     signal: controller.signal
    }); 
  clearTimeout(timeoutId);
const data = await response.json();

if (data.status) {
  setAccounts(data.accounts); 
  setPanel("searchAccounts");
} else {
  setAccounts([]);
  setPanel("searchAccounts");
}
    }
    catch(err) {
  console.error("Account searched failed", err);
    }
  }

const [activePanel,setPanel]=useState(null);
const handleDisplay =(activePanel)=> {
  setPanel(activePanel);

}
return (
  <div className="dashboard-container">
  <div className="dashboard-wrapper">
    {notification && (
      <Notification
        message={notification.message}
        type={notification.type}
        onClose={() => setNotification(null)}
      />
    )}

    <nav className="navbar_menu">
      <div className="navbar-left">
        <span className="user-name">Profile type: {userType}</span>
        <span className="user-id">Personal ID: {userId}</span>
      </div>
      <div className="navbar-right">
        <button className="logout-button" onClick={handleAction}>Log Out</button>
      </div>
    </nav>

    <div className="dashBoard">
      <div className="left_menu">
        <button className="account-button" onClick={() => handleDisplay("createAccount")}>Create Account</button>
        <button className="search-button" onClick={handleSearchAccount}>Search Account</button>
      </div>

      <div className="main_view">
        {activePanel === "yes" && (
          <section className="account-profile-section">
            <div className="account-profile">
              <h2>Account Profile</h2>
              <div className="account-info">
                <p><strong>Account Number:</strong> {enteredAccountNumber}</p>
                <p><strong>Account Type:</strong> {getCurrentAccountType(selectedType)}</p>
                <p><strong>Balance:</strong> <weak>$</weak>{balance}</p>
              </div>

              <div className="actions">
                {/* Show buttons only if no subpanel is active */}
                {activeSubPanel === null && (
                  <>
                    <button className="btn" onClick={() => setSubPanel("deposit")}>💰 Deposit Money</button>
                    <button className="btn" onClick={() => setSubPanel("withdraw")}>🏧 Withdraw Money</button>
                    <button className="btn" onClick={() => setSubPanel("createTrans")}>🔄 Create Transaction</button>
                    <button className="btn" onClick={() => setSubPanel("transactions")}>📜 Transactions</button>
                    <button className="btn" onClick={async () => { await handleHistory(); setSubPanel("transactionsHistory")}}>📜 Transaction History</button>
                  </>
                )}

                {/* Render only the active subpanel */}
                {activeSubPanel === "deposit" && (
                  <Deposit
                    depositAmount={depositAmount}
                    setDepositAmount={setDepositAmount}
                    handleDeposit={handleDeposit}
                    setSubPanel={setSubPanel}
                  />
                )}

                {activeSubPanel === "withdraw" && (
                  <Withdraw
                    withdrawAmount={withdrawAmount}
                    setWithdrawAmount={setWithdrawAmount}
                    handleWithdraw={handleWithdraw}
                    setSubPanel={setSubPanel}
                  />
                )}

                {activeSubPanel === "createTrans" && (
                  <CreateTransaction
             toAccount={toAccount}
             setToAccount={setToAccount}
             transactionSum={transactionSum}
             setTransactionSum={setTransactionSum}
             typeTransaction={typeTransaction}
             setTypeTransaction={setTypeTransaction}
             setSubPanel={setSubPanel}
             handleTransaction={handleTransaction}
             pending={pending}
             setPending={setPending}
                  />
                )}

                {activeSubPanel === "transactions" && (
                 <Transaction
                 setTransactionsView={setTransactionsView}
                 handleInboxGet={handleInboxGet}
                 handleSentGet={handleSentGet}
                 inboxTransactions={inboxTransactions}
                 sentTransactions={sentTransactions}
                 handleAccept={handleAccept}
                 handleDecline={handleDecline}
                 setSubPanel={setSubPanel}
                 transactionType={transactionType}
                 transactionsView={transactionsView}  
                 loadingSent={loadingSent}
                 transactionToConfirm={transactionToConfirm}
                 setTransactionToConfirm={setTransactionToConfirm}
                 actionType={actionType}
                 setActionType={setActionType}
            />

                )}

                {activeSubPanel === "transactionsHistory" && (
                  transactionHistory.length > 0 ? (
                    <TransactionHistory
                      transactionHistory={transactionHistory}
                      handleDelete={handleDelete}
                      transactionType={transactionType}
                       setSubPanel={setSubPanel}
                       setTransactionToDelete={setTransactionToDelete}
                       transactionToDelete={transactionToDelete}
                          />
                            
                    
                  ) : (
               <div>
             <p className="empty-message">📝 No transaction history</p>
             <button className="btn" onClick={() => setSubPanel(null)}>Back</button>
             </div>
                  )
                )}
              </div>
            </div>
          </section>
        )}

        {activePanel === null && (
          <div className="main-default">
            <h2>Welcome!</h2>
            <p>Choose an option from the menu on the left to get started.</p>
            <img src={bankLogo} alt="Main Menu Guide" className="menuGuideImg" />
          </div>
        )}

        {activePanel === "createAccount" && (
          <CreateAccount
            enteredAccountNumber={enteredAccountNumber}
            handleLogin={handleLogin}
            setEnterID={setEnterID}
            selectedType={selectedType}
            setType={setType}
          />
        )}

        {activePanel === "searchAccounts" && (
          <section className="accounts-section">
            <h2>Your Accounts</h2>
            {accounts && accounts.length > 0 ? (
              <SearchAccount
                accounts={accounts}
                handleOpenProfile={handleOpenProfile}
                getAccountType={getAccountType}
              />
            ) : (
              <p>No accounts found.</p>
            )}
          </section>
        )}
      </div> {/* end of main_view */}

      <div className="right_menu">
        <img src={profilImage} alt="profile picture"/>
        <span className="profile-type">{userName}</span>
      </div>
    </div> 
  </div> 
</div> 
);};
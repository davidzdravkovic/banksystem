 import React from "react"
 
 const CreateAccount = ({setEnterID,setType,selectedType,handleLogin,enteredAccountNumber}) => {
  return (
                 <form onSubmit={handleLogin}>
               <section className="create-account">
                <h1 className="Title">Account Creation!</h1>
                <p>Enter account number:</p>
                <input
                  type="text"
                  value={enteredAccountNumber}
                  onChange={(e) => setEnterID(e.target.value)}
                  pattern="\d+"
                  title="Only numbers allowed"
                />
                <p>Choose the type of account you want:</p>
                <select value={selectedType} onChange={(e) => setType(e.target.value)} required>
                  <option value="">-- Select account type --</option>
                  <option value="CheckingAccount">Checking</option>
                  <option value="SavingsAccount">Savings</option>
                  <option value="CreditAccount">Credit</option>
                </select>
                <button type="submit">Create Account</button>
              </section>
            </form>
 );};


const SearchAccount = ({accounts,handleOpenProfile,getAccountType}) => {
  return (  <table className="accounts-table">
                  <thead>
                    <tr>
                      <th>Account Number</th>
                      <th>Account Type</th>
                      <th>Balance</th>
                      <th>Action</th>
                    </tr>
                  </thead>
                  <tbody>
                    {accounts.map((acc, index) => (
                      <tr key={index}>
                        <td>{acc.accountNumber}</td>
                        <td>{getAccountType(acc.accountType)}</td>
                        <td>{acc.balance ?? "—"}</td>
                        <td>
                          <button onClick={() => handleOpenProfile(acc)}>Select</button>
                        </td>
                      </tr>
                    ))}
                  </tbody>
                </table>
               ); };
 export {CreateAccount,SearchAccount};
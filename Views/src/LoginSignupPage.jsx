import React from "react";
import { useNavigate } from "react-router-dom";
import bankLogo from "./images/bank_logo.png";

export default function LoginSignupPage () {
  const navigate=useNavigate()

const handleAction = (action) => {
  navigate("/usertype",{state:{action}});
}
return (
  <div className="container"> 
  <div className="content-wrapper">
    <header className="header"> 
     <img src={bankLogo} alt="Bank Logo" className="logo"
    
     /> <h1 className="welcome-title"> Welcome to bank application! </h1> </header>
      <main className="main">
      <button className="btn" onClick={() => handleAction("signup")}> Sign Up </button>
      <button className="btn" onClick={() => handleAction("login")}> Log In </button> 
          </main> 
         </div>
         </div>
)
}
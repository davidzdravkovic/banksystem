
import React, { useState } from "react";
import { useLocation, useNavigate } from "react-router-dom";

export default function LoginPage() {
  const navigate=useNavigate();
  const location = useLocation();
 const userType = location.state?.userType || "personal";
  const [personalID, setPersonalId] = useState("");
  const [password, setPassword] = useState("");

  const handleLogin = async () => {
  try {
    const response = await fetch("http://localhost:8080/users/login", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ 
  personalID: parseInt(personalID), // convert input string to integer
  password,
  type: userType
  
})


    });

    // Check if server responded with success status
    if (!response.ok) {
      // Server returned error status (400, 401, 500, etc.)
      const text = await response.text(); // read response body
      throw new Error(`Server error: ${text}`);
    }

    // Parse JSON safely
    const data = await response.json();

    if (data.success) {
      localStorage.setItem("userId", data.userId);
      localStorage.setItem("userName", data.userName);
      localStorage.setItem("userType", data.userType);
      localStorage.setItem("token", data.token);
      navigate("/ProfileDashBoard");
    } else {
      alert("Wrong personal ID or password!");
    }

  } catch (err) {
    if (err.name === "AbortError") {
      alert("Request timed out. Please try again.");
    } else {
      console.error("Login error:", err.message);
      alert(`Login failed: ${err.message}`);
    }
  }
};

 
  

  return (
    <div className="container">
      <div className="content-wrapper">
      <h2>{userType.charAt(0).toUpperCase() + userType.slice(1)} Login</h2>
        <input
          type="text"
          placeholder="Personal ID"
          value={personalID}
          onChange={(e) => setPersonalId(e.target.value)}
        />
        <input
          type="password"
          placeholder="Password"
          value={password}
          onChange={(e) => setPassword(e.target.value)}
        />
        <button className="btn" onClick={handleLogin}>
       Submit
        </button>
      </div>
    </div>
  );
};

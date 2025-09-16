import React, { useState } from "react";
import { useNavigate, useLocation } from "react-router-dom";

export default function SignupPage() {
  const navigate = useNavigate();
  const location = useLocation();
  const userType = location.state?.userType || "personal";

  // Common fields
  const [fullName, setFullName] = useState("");
  const [personalID, setPersonalID] = useState("");
  const [password, setPassword] = useState("");

  // Business-specific fields
  const [businessAddress, setBusinessAddress] = useState("");
  const [businessContact, setBusinessContact] = useState("");
  const [registerNumber, setRegisterNumber] = useState("");

  // Student-specific fields
  const [age, setAge] = useState("");
  const [studentID, setStudentID] = useState("");
  const [typeEducation, setTypeEducation] = useState("");

  const handleSubmit = (e) => {
    e.preventDefault();

    // Build user data based on type
    const userData = { fullName, personalID: Number(personalID), password, userType };

    if (userType === "business") {
      userData.businessAddress = businessAddress;
      userData.businessContact = Number(businessContact);
      if (registerNumber) userData.registerNumber = registerNumber;
    }

    if (userType === "student") {
      userData.age = Number(age);
      userData.studentID = Number(studentID);
      userData.typeEducation = typeEducation;
    }

    // Send to backend
    fetch(`http://localhost:8080/users/signup?userType=${userType}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(userData),
    })
      .then(async (res) => {
        if (!res.ok) {
          const text = await res.text();
          console.error("Server error:", text);
          return;
        }
        const data = await res.json();
        console.log(data);

        if (data.success) {
          localStorage.setItem("userId", data.userId);
          localStorage.setItem("userName", data.userName);
          localStorage.setItem("userType", data.userType);
          localStorage.setItem("token", data.token);
          navigate("/ProfileDashBoard");
        }
      })
      .catch((err) => console.error("Fetch failed:", err));
  };

  return (
    <div className="signup-form">
      <h2>
        {userType === "business" && "Business User Signup"}
        {userType === "personal" && "Personal User Signup"}
        {userType === "student" && "Student User Signup"}
      </h2>

      <form onSubmit={handleSubmit}>
        {/* Common fields */}
        <div>
          <label>Full Name:</label>
          <input type="text" value={fullName} onChange={(e) => setFullName(e.target.value)} required />
        </div>
        <div>
          <label>Personal ID:</label>
          <input type="number" value={personalID} onChange={(e) => setPersonalID(e.target.value)} required />
        </div>
        <div>
          <label>Password:</label>
          <input type="password" value={password} onChange={(e) => setPassword(e.target.value)} required />
        </div>

        {/* Business fields */}
        {userType === "business" && (
          <>
            <div>
              <label>Business Address:</label>
              <input type="text" value={businessAddress} onChange={(e) => setBusinessAddress(e.target.value)} required />
            </div>
            <div>
              <label>Business Contact:</label>
              <input type="number" value={businessContact} onChange={(e) => setBusinessContact(e.target.value)} required />
            </div>
            <div>
              <label>Register Number (optional):</label>
              <input type="number" value={registerNumber} onChange={(e) => setRegisterNumber(e.target.value)} />
            </div>
          </>
        )}

        {/* Student fields */}
        {userType === "student" && (
          <>
            <div>
              <label>Age:</label>
              <input type="number" value={age} onChange={(e) => setAge(e.target.value)} required />
            </div>
            <div>
              <label>Student ID:</label>
              <input type="number" value={studentID} onChange={(e) => setStudentID(e.target.value)} required />
            </div>
            <div>
              <label>Type of Education:</label>
              <input type="text" value={typeEducation} onChange={(e) => setTypeEducation(e.target.value)} required />
            </div>
          </>
        )}

        <button type="submit">Sign Up</button>
      </form>
    </div>
  );
}

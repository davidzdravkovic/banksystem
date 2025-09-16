import React from "react";
import { useNavigate, useLocation } from "react-router-dom";

export default function UserTypePage() {
  const navigate = useNavigate();
  const location = useLocation();

  // Get the action from previous page: "login" or "signup"
  const action = location.state?.action || "login";

  const handleSelect = (type) => {
    // Navigate to the correct page based on action
    if (action === "login") {
      navigate("/login", { state: { userType: type } });
    } else if (action === "signup") {
      navigate("/signup", { state: { userType: type } });
    }
  };

  return (
    <div className="container">
      <div className="content-wrapper">
        <h2>Select User Type</h2>
        <div className="main">
          <button className="btn" onClick={() => handleSelect("personal")}>
            Personal User
          </button>
          <button className="btn" onClick={() => handleSelect("business")}>
            Business User
          </button>
          <button className="btn" onClick={() => handleSelect("student")}>
            Student User
          </button>
        </div>
      </div>
    </div>
  );
}

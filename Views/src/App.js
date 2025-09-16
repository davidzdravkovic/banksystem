import React from "react";
import { HashRouter as Router, Routes, Route } from "react-router-dom";


// Pages
import LoginSignupPage from "./LoginSignupPage";
import UserTypePage from "./UserTypePage";
import LoginPage from "./LoginPage";
import SignupPage from "./SignupPage";
import ProfileDashboard from "./ProfileDashboardPages/ProfileDashboard";


function App() {
  return (
    <Router>
      <Routes>
        {/* Step 1: Choose Log In or Sign Up */}
        <Route path="/" element={<LoginSignupPage />} />

        {/* Step 2: Choose User Type */}
        <Route path="/usertype" element={<UserTypePage />} />

        {/* Step 3: Login form */}
        <Route path="/login" element={<LoginPage />} />

        {/* Step 4: Sign Up form */}
        <Route path="/signup" element={<SignupPage />} />
         {/* Step 5: Dashboard form*/}
        <Route path="/profiledashboard" element={<ProfileDashboard />} />

      </Routes>
    </Router>
  );
}

export default App;

import React from "react";


const Notification = ({ message, type, onClose }) => {
  return (
    <div className={`notification ${type}`}>
      {message}
      <button onClick={onClose}>✖</button>
    </div>
  );
};

export default Notification;

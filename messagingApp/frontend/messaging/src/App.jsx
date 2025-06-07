import React from "react";
import MessageList from "./compoennts/MessagesList";
import MessageForm from "./components/MessageForm";
import React, {useState, useEffect, useRef} from 'react';
import {Send, Users, MessageCircle, LogOut, UserPlus} from 'lucide-react';

const API_BASE = 'http://localhost:8080/api';
const WS_URL = 'ws://localhost:8080/ws';

const MessaggingApp=()=>{
  const [user, setUser]=useState(null);
  const [users, setUsers]=useState([]);
  const [selectedUser, setSelectedUser]=useState(null);
  const [messages, setMessages]=useState([]);
  const [newMessage, setNewMessage]=useState('');
  const [showLogin, setShowLogin]=useState(true);
  const [showRegister, setShowRegister]= useState(false);
  const [loginData, setLoginData]=useState({name:'', password: ''});
  const [registerData, setRegisterData]=useState({username:'', email:'', password:''});
  const [error, setError]=useState('');
  const [loading, setLoading]=useState(false);
  const wsRef=useRef(null);
  const messagesEndRef=useRef(null);

  useEffect(()=>{
    if (user){
      wsRef.current=new WebSocket(WS_URL);
      wsRef.current.onopen=()=>{
        console.log('WebSocket connected');
        wsRef.current.send(JSON.stringify({
          type:'auth',
          user_id:user.id
        }));
      };

      wsRef.current.onmessage=(event)=>{
        const data=JSON.parse(event.data){
        if (data.type=='new_message'){
          if (data.send_id==user.id && data.receiver_)
        }
        }
      }
    }
  })
}
const App=()=>{
  const [refresh, setRefresh]=React.useState(false);

  const handleNewMessage=()=>{
    setRefresh(!refresh);
};


  return (
    <div>
    <h1>Messaging App</h1>
    <MessageForm onMessageSent={handleNewMessage} />
    <MessageList key={refresh} />
  </div>
  );
};

export default App;

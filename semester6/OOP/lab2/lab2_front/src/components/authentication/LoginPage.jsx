import React from "react";
import {executeLogin} from "../../redux/reducers/loginReducer";
import {Redirect} from "react-router";
import {connect} from "react-redux";

class LoginPage extends React.Component{

    constructor(props){
        super(props)

        this.state={
            username:"",
            password:""
        }
    }

    onInputChange =(event)=>{
        this.setState({
                [event.target.name]: event.target.value
            }
        )
    }

    onLoginClicked=()=>{
        this.props.executeLogin(this.state.username,this.state.password);
    }

    render() {
        if(this.props.isLogged)
            return <Redirect to="/" />

        return (
          <div className="container">
              <div className="row">
                  <div className="col-md-6 m-auto">
                      <h1>Payments</h1>
                      {this.props.isLoginFailed && <div className="alert alert-warning">Invalid credentials</div>}
                      <input style={{marginTop: '1rem'}} type="text" name="username" placeholder="username" className="form-control" value={this.state.username} onChange={this.onInputChange}/>
                      <input style={{marginTop: '1rem'}} type="password" name="password" placeholder="password" className="form-control" value={this.state.password} onChange={this.onInputChange}/>
                      <button style={{marginTop: '1rem'}}  className="btn btn-warning btn-block" name="loginButton" onClick={this.onLoginClicked}>Sign in</button>
                  </div>
              </div>
          </div>
        );
    }
}

function mapStateToProps(state){
    return{
        isLoginFailed:state.loginReducer.isLoginFailed,
        isLoading:state.loginReducer.isLoading,
        isLogged:state.loginReducer.isLogged
    }
}

function mapDispatchToProps(dispatch){
    return{
        executeLogin:(username,password)=>dispatch(executeLogin(username,password))
    }
}

export default connect(mapStateToProps,mapDispatchToProps)(LoginPage);
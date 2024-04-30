const LocalStrategy = require("passport-local").Strategy
const bcrypt = require("bcrypt")
const { Passport } = require("passport")
//const {authenticate } = require("passport") //PROBABLY NOT NEEDED

function initialize(passport, getUserByEmail, getUserById){

    // function to authenticate users
    const authenticateUsers = async(email, password, done)=> {
        //get users by email 
        const user = getUserByEmail(email)
        if (user == null){
            return done(null, false, {message: "No user found with that email"})

        }
        try{
            if(await bcrypt.compare(password, user.password)){
                return done(null, user)
 
            } else{
                return done(null, false, {message: "password incorrect"})
            }
        } catch(e){
            console.log(e);
            return done(e)
        }
    }
    passport.use(new LocalStrategy({usernameField: 'email'}, authenticateUsers))
    passport.serializeUser((user, done) => done(null, user.id)) //CODE IS WORKING WHEN THIS IS COMMENTED
    passport.deserializeUser((id, done) => {
        return done(null, getUserById(id))
    })
}
module.exports = initialize


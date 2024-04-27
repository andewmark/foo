if(process.env.NODE_ENV !== "production"){
    require("dotenv").config()
}


//importing libraries that we installed using npm
const express = require("express") //we imported express using npm
const app = express()
const bcrypt = require("bcrypt") // importing bcrypt package 
const passport = require("passport")
const initializePassport = require("./passport-config")
const flash = require("express-flash")
const session = require("express-session")

// for the login authentication 
initializePassport(
    passport,
    email => users.find(user => user.email == email), // cheking the email we got from the user
    id => users.find(user => user.id == id)
)


// instead of using an advanced db to store data, we're using an array
const users = []



app.use(express.urlencoded({extended: false})) // allows us to get the inputs that the user put in eg: username, password, email
app.use(flash())
app.use(session({
    secret: process.env.SECRET_KEY,
    resave: false, // we wont resave the session is nothing is saved
    saveUninitialized: false
}))

app.use(passport.initialize())
app.use(passport.session())

// configuring the login post functionality 
app.post("/login",checkNotAuthenticated, passport.authenticate("local", {
    successRedirect: "/", // ADD HOMEPAGE HERE
    failureRedirect: "/login",
    failureFlash: true 
}))


// configuring the register post functionality 

app.post("/register", checkNotAuthenticated, async (req, res) =>{
    try {
        const hashedPassword = await bcrypt.hash(req.body.password, 10) // the 10 is the standard way of hashing passwords
        users.push({
            id: Date.now().toString(),
            username: req.body.username, 
            email: req.body.email,
            password: hashedPassword, // instead of calling it the way we did the rest. we just call the hashedpassword so that it is hashed
        })
        console.log(users); // display newly registered users in the console
        res.redirect("/login") // if this is a success, we redirect the user to the login page

    }catch(e){
        console.log(e); // to give the user an error
        res.redirect("/register")  

    }
})

//routes
// ADD THE HOMEPAGE AFTER THE "/"
app.get('/', checkAuthenticated, (req, res) => { // in the res is where we write all our html code
    res.render("index.ejs" , {name: req.user.name}) // we use render to pass the template
})

app.get('/login', checkNotAuthenticated, (req, res) => {
    res.render("login.ejs")
})

app.get('/register', checkNotAuthenticated, (req, res) => {
    res.render("register.ejs")
})

// end routes
app.delete("logout", (req,res)=>{
    req.logOut()
    res.redirect("/login")
})

function checkAuthenticated(req, res, next){
    if(req.isAuthenticated()){
        return next()

    }
    res.redirect("/login")
}
function checkNotAuthenticated(req, res, next){
    if(req.isAuthenticated()){
        return res.redirect("/")
    }
    next()
}
app.listen(3000)

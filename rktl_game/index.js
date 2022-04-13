// Connecting to ROS
// -----------------

var ros = new ROSLIB.Ros({
    url: 'ws://172.17.0.2:9090'
});

ros.on('connection', function () {
    console.log('Connected to websocket server.');
});

ros.on('error', function (error) {
    console.log('Error connecting to websocket server: ', error);
});

ros.on('close', function () {
    console.log('Connection to websocket server closed.');
});


// Subscribe to the game manager node

var statusListener = new ROSLIB.Topic({
    ros: ros,
    name: '/match_status',
    messageType: 'rktl_msgs/MatchStatus'
});

// Creating the service objects called by the buttons

var pause_srv = new ROSLIB.Service({
    ros: ros,
    name: 'pause_game',
    serviceType: 'std_srvs/Empty'
});

var unpause_srv = new ROSLIB.Service({
    ros: ros,
    name: 'unpause_game',
    serviceType: 'std_srvs/Empty'
});

var reset_srv = new ROSLIB.Service({
    ros: ros,
    name: 'clock_set',
    serviceType: 'std_srvs/Empty'
});

// Game clock parameters

var game_time_param = new ROSLIB.Param({
    ros: ros,
    name: '/game_length'
});

function set_game_time() {
    var time = document.getElementById('time-set').value;
    time = parseInt(time);
    game_time_param.set(time);
    reset_srv.callService();
}

// updating the score on a timer

const interval = setInterval(function () {
    statusListener.subscribe(function (message) {
        document.getElementById('blue-score').innerHTML = message.score.blue;
        document.getElementById('orange-score').innerHTML = message.score.orange;
        document.getElementById('timer').innerHTML = message.clock;
        console.log(message.status);
    });
}, 1000);
const osc = require('./osc.js');

async function run() {
	setInterval(() => {
		osc.sendValue(
			`/d0`,
			127
		);
	},1000);
}

run().catch(err => {
	log('Ouch!');
	log(err);
});

window.addEventListener('load', () => {
    const websocket = new WebSocket(`ws://${window.location.hostname}/ws`);

    websocket.onopen = (e) => console.log('connected', e);
    websocket.onerror = (e) => console.log('error', e);
    websocket.onmessage = (e) => {
        const { humidity, temperature } = JSON.parse(e.data);
        document.getElementById('humidity').innerHTML = humidity || 'No data';
        document.getElementById('temperature').innerHTML = temperature || 'No data';
    };
});

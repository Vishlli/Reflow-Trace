import mqtt from 'mqtt';

const BROKER_URL = 'wss://broker.hivemq.com:8884/mqtt';
const TOPIC = 'reflow-trace/sachin0317-demo/bin/BLOCK-D-04';

export type BinReading = {
  point: string;
  distance: number;
  fill: number;
  status: 'NORMAL' | 'COLLECTION_REQUIRED';
  alert: boolean;
  uptimeMs: number;
};

export function startBinFeed(onReading: (r: BinReading) => void) {
  const client = mqtt.connect(BROKER_URL, {
    clientId: 'reflow-web-' + Math.random().toString(16).slice(2, 10),
    reconnectPeriod: 3000,
  });

  client.on('connect', () => {
    console.log('[MQTT] connected');
    client.subscribe(TOPIC, (err) => {
      if (err) console.error('[MQTT] subscribe failed', err);
      else console.log('[MQTT] subscribed to', TOPIC);
    });
  });

  client.on('message', (_topic, payload) => {
    try {
      onReading(JSON.parse(payload.toString()) as BinReading);
    } catch (e) {
      console.error('[MQTT] bad payload', payload.toString(), e);
    }
  });

  client.on('error', (e) => console.error('[MQTT] error', e));

  return () => client.end();
}
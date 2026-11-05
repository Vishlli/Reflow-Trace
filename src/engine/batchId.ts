const ALPHABET = '23456789ABCDEFGHJKMNPQRSTUVWXYZ';

function randomSuffix(length: number): string {
  const bytes = new Uint8Array(length);
  crypto.getRandomValues(bytes);
  return Array.from(bytes, (byte) => ALPHABET[byte % ALPHABET.length]).join('');
}

export function generateBatchId(pointId: string, createdAt: Date, existingIds: Set<string>): string {
  const day = createdAt.toISOString().slice(0, 10).replace(/-/g, '');
  const pointCode = pointId.replace(/^DP-/, '').replace(/-/g, '');
  let id: string;
  do {
    id = `MW-${day}-${pointCode}-${randomSuffix(4)}`;
  } while (existingIds.has(id));
  return id;
}
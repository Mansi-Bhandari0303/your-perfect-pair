const recommendations = {
  Oval: { copy: 'Balanced proportions work beautifully with both soft and structured frames.', observations: ['Face length is slightly greater than its width.', 'The jawline appears softly rounded.', 'Proportions are naturally balanced.'], styles: [['Soft rectangles', 'Add definition while keeping your natural balance.'], ['Classic wayfarers', 'Give the face a little structure without overpowering it.'], ['Rounded metal frames', 'Echo the softer jawline for an easy everyday look.']], avoid: ['Frames much narrower than your cheekbones', 'Very heavy oversized frames'] },
  Round: { copy: 'Angular contrast will add definition to softer facial curves.', observations: ['Face width and length are fairly similar.', 'The cheek and jaw lines look softly curved.', 'Angular contrast will add definition.'], styles: [['Angular rectangles', 'Sharper lines balance softer facial curves.'], ['Browline frames', 'A stronger upper edge adds visual lift.'], ['Geometric frames', 'Crisp angles create flattering contrast.']], avoid: ['Very small round frames', 'Frames with a low, narrow bridge'] },
  Square: { copy: 'Curved lines will soften your defined jaw while keeping your look polished.', observations: ['Forehead, cheeks, and jaw have similar widths.', 'The jawline has a clear, defined shape.', 'Curved lines will soften the overall impression.'], styles: [['Rounded rectangles', 'Keep structure while softening strong angles.'], ['Oval frames', 'Create a smooth contrast with the jawline.'], ['Thin metal frames', 'Add polish without adding visual weight.']], avoid: ['Very boxy frames with thick corners', 'Frames wider than your face'] },
  Heart: { copy: 'Balanced lower-weight frames create harmony with a wider forehead.', observations: ['The forehead is wider than the lower face.', 'Cheekbones are a noticeable feature.', 'The chin and jaw taper more narrowly.'], styles: [['Bottom-heavy frames', 'Add visual balance to the lower face.'], ['Light oval frames', 'Keep the upper face feeling open.'], ['Rimless frames', 'Offer a subtle look with very little weight.']], avoid: ['Very top-heavy frames', 'Very high, thick browlines'] },
  Diamond: { copy: 'Lifted and curved frame lines complement your standout cheekbones.', observations: ['Cheekbones are the strongest horizontal feature.', 'The forehead and jaw taper more narrowly.', 'Curved or lifted lines complement the cheekbones.'], styles: [['Cat-eye frames', 'Lift the eye line and complement prominent cheeks.'], ['Oval frames', 'Soften the angular proportions.'], ['Browline frames', 'Draw attention upward in a balanced way.']], avoid: ['Very narrow frames', 'Frames ending exactly at the widest cheek point'] },
  Oblong: { copy: 'Deeper frames add proportion and balance to a longer face shape.', observations: ['The face appears longer than it is wide.', 'The cheek and jaw lines are relatively straight.', 'Deeper frames can add proportion and balance.'], styles: [['Deep rectangular frames', 'Add visual depth to a longer face.'], ['Oversized round frames', 'Bring width and softness to the proportions.'], ['Low-bridge styles', 'Help the frame sit comfortably and securely.']], avoid: ['Very shallow lens heights', 'Extremely narrow frames'] }
};

const palettes = {
  Warm: [['Warm tortoiseshell', 'Rich contrast with golden warmth.', '#9b633e'], ['Honey brown', 'Soft and easy for everyday wear.', '#b78761'], ['Olive', 'A muted colour that still feels distinctive.', '#737755'], ['Brushed gold', 'Adds warmth without looking too bright.', '#bd945d']],
  Cool: [['Cool tortoiseshell', 'Adds depth without yellow undertones.', '#594d4a'], ['Charcoal', 'A polished alternative to solid black.', '#4a4a49'], ['Deep navy', 'A quiet colour with flattering contrast.', '#283b54'], ['Silver', 'Works cleanly with cooler undertones.', '#a7a9aa']],
  Neutral: [['Soft black', 'A dependable choice with clear definition.', '#272523'], ['Neutral tortoiseshell', 'Adds texture while staying versatile.', '#80634f'], ['Clear crystal', 'Keeps the look light and modern.', '#d7d1c8'], ['Champagne metal', 'A balanced metallic that is easy to wear.', '#c2a476']]
};

const form = document.querySelector('#pair-form');
const shapePreview = document.querySelector('#preview-shape');
const previewCopy = document.querySelector('#preview-copy');
const result = document.querySelector('#result');

function selected(name) { return document.querySelector(`input[name="${name}"]:checked`).value; }
function item(title, text) { return `<div class="result-item"><b>${title}</b><small>${text}</small></div>`; }
function normalize(value) { return String(value ?? '').trim().toLowerCase(); }
function parsePrescription(rawValue) {
  const value = normalize(rawValue);
  if (!value) return 0;

  const match = value.match(/-?\d+(?:\.\d+)?/);
  if (!match) return 0;

  const numericValue = Number(match[0]);
  return Number.isFinite(numericValue) ? Math.abs(numericValue) : 0;
}
function buildLensOptions(purpose, prescriptionStrength) {
  const options = [
    ['Anti-reflective coating', 'Useful for screen work, photos, and night-time glare.'],
    ['UV protection', 'A sensible everyday protection feature for outdoor use.'],
    ['High-index lenses', prescriptionStrength >= 4
      ? 'Worth discussing with an optician for a stronger prescription.'
      : 'Ask an optician whether the thinner profile benefits your prescription.']
  ];

  if (/(sport|sports|cycling|running|fitness|active|athletics|outdoor)/.test(normalize(purpose))) {
    options.push(['Impact-resistant material', 'A practical option for active use; confirm the right material with an optician.']);
  }

  return options;
}

document.querySelectorAll('input[name="shape"]').forEach((input) => input.addEventListener('change', () => {
  const data = recommendations[selected('shape')];
  shapePreview.textContent = selected('shape');
  previewCopy.textContent = data.copy;
}));

form.addEventListener('submit', (event) => {
  event.preventDefault();
  const shape = selected('shape');
  const tone = selected('tone');
  const purpose = document.querySelector('#purpose').value;
  const prescriptionStrength = parsePrescription(document.querySelector('#prescription').value);
  const data = recommendations[shape];

  document.querySelector('#result-title').textContent = `${shape} face shape`;
  document.querySelector('#result-summary').textContent = `${data.copy} ${purpose ? `For “${purpose}”, this is a practical starting point.` : 'Your personalised starting point is ready below.'}`;
  document.querySelector('#observations').innerHTML = data.observations.map((value) => `<span>${value}</span>`).join('');
  document.querySelector('#styles').innerHTML = data.styles.map(([title, text]) => item(title, text)).join('');
  document.querySelector('#colors').innerHTML = palettes[tone].map(([title, text, color]) => `<div class="color-item"><span class="color-swatch" style="background:${color}"></span>${item(title, text)}</div>`).join('');
  document.querySelector('#lenses').innerHTML = buildLensOptions(purpose, prescriptionStrength).map(([title, text]) => item(title, text)).join('');
  document.querySelector('#avoid').innerHTML = data.avoid.map((value) => `<span class="result-item">${value}</span>`).join('');
  result.hidden = false;
  result.scrollIntoView({ behavior: 'smooth', block: 'start' });
});

document.querySelector('#reset-button').addEventListener('click', () => {
  result.hidden = true;
  window.scrollTo({ top: 0, behavior: 'smooth' });
});